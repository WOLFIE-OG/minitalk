# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    actions_runner.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 11:56:46 by otodd             #+#    #+#              #
#    Updated: 2024/12/04 22:45:44 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import logging
from copy import deepcopy
from yaml import safe_load
from subprocess import Popen, PIPE
from uuid import uuid4
from pathlib import Path
from git import Repo
from git.util import RemoteProgress

COLORS = {
    "DEBUG": "\033[94m",
    "INFO": "\033[92m",
    "WARNING": "\033[93m",
    "ERROR": "\033[91m",
    "CRITICAL": "\033[95m",
    "RESET": "\033[0m",
}
LOG_FORMAT = "[%(levelname)s] :: [%(asctime)s] :: %(message)s"
WORKFLOW_DIR = Path(".github/workflows/")
TMP_DIR = Path("/tmp/actions_runner/")
REPO = Repo(os.getcwd())

class ColoredFormatter(logging.Formatter):
    def format(self, record: logging.LogRecord):
        color = COLORS.get(record.levelname, COLORS["RESET"])
        r = deepcopy(record)
        r.levelname = f"{color}{r.levelname}{COLORS['RESET']}"
        return super().format(r)

class Progress(RemoteProgress):
    def update(self, *args):
        logger.debug(self._cur_line)

logger = logging.getLogger("actions_runner")
logger.setLevel(logging.DEBUG)

console_handler = logging.StreamHandler()
console_handler.setFormatter(ColoredFormatter(LOG_FORMAT, datefmt="%Y-%m-%d %H:%M:%S"))
console_handler.setLevel(logging.DEBUG)
logger.addHandler(console_handler)

_id = REPO.remotes[0].name + '_' + REPO.branches[0].name + '_' + uuid4().__str__()
file_handler = logging.FileHandler(Path(_id + ".log"))
file_handler.setFormatter(
    logging.Formatter(LOG_FORMAT, datefmt="%Y-%m-%d %H:%M:%S")
)
file_handler.setLevel(logging.DEBUG)
logger.addHandler(file_handler)

logger.debug("Fetching repo url")
repo_url =  REPO.remotes[0].url
repo_dir = Path(TMP_DIR.__str__() + '/' + os.getcwd().split("/")[0] + uuid4().__str__())
logger.debug("Creating repo dir")
os.mkdir(repo_dir)

logger.debug("Checking tmp folder")
if not os.path.exists(TMP_DIR):
    os.mkdir(TMP_DIR)

logger.debug("Checking workflows folder")
if not os.path.exists(WORKFLOW_DIR):
    logger.critical("Workflows folder not found!!! Exiting")
    exit(1)

logger.debug(f"Cloning [{repo_url}] into {repo_dir}")
Repo.clone_from(
    multi_options=["--recursive"], to_path=repo_dir, url=repo_url, progress=Progress()
)

for workflow in os.listdir(WORKFLOW_DIR):
    logger.debug(f"Parsing workflow file {workflow}")
    with open(Path(WORKFLOW_DIR.__str__() + '/' + workflow)) as f:
        action = safe_load(f)

    for job in action["jobs"]:
        env = action["jobs"][job].get("env")
        env_i = [item for item in action["jobs"][job].get("env").keys()]
        logger.debug(f"Running steps for {action.get("name")} on job {job}")
        length = len(action["jobs"][job].get("steps"))
        for index, step in enumerate(action["jobs"][job].get("steps")):
            if not step.get("run"):
                continue
            logger.info(
                f"{10 * '='}| Running step ({index} / {length}): {step.get("name")} |{10 * '='}"
            )
            out = PIPE
            cmd_prep: str = step.get("run")
            for i in env_i:
                cmd_prep = cmd_prep.replace(f"${i}", env.get(i))
            proc = Popen(
                cmd_prep,
                stdout=out,
                stderr=out,
                cwd=(
                    Path(repo_dir.__str__() + '/' + step.get("working-directory"))
                    if step.get("working-directory")
                    else Path(repo_dir)
                ),
                shell=True,
            )
            logger.debug(f"{5 * '='}| [ Step stdout start ] |{5 * '='}\n")
            while True:
                line = proc.stdout.readline()
                if not line:
                    break
                try:
                    line = line.decode("utf-8")
                except UnicodeDecodeError:
                    line = line.decode("unicode_escape")
                print(line.strip())
                file_handler.stream.write(line)
            ret = proc.wait(500)
            if ret != 0:
                logger.info(f"{5 * '='} [ Step stdout finish ] {5 * '='}")
                logger.error(f"{4 * '-'}| Step {index} failed! |{4 * '-'}")
                logger.error(f"CMD [{step.get("run")}]")
                logger.error(f"{5 * '='} [ Step stderr start ] {5 * '='}\n")
                while True:
                    line = proc.stderr.readline()
                    if not line:
                        break
                    try:
                        line = line.decode("utf-8")
                    except UnicodeDecodeError:
                        line = line.decode("unicode_escape")
                    print(line.strip())
                    file_handler.stream.write(line)
                logger.error(f" {5 * '='} [ Step stderr finish ] {5 * '='}")
                if step.get("continue-on-error", False) != True:
                    exit()
                    logger.info("Exiting")
            logger.info(f"{5 * '='} [ Step stdout finish ] {5 * '='}")
            logger.info(f"{10 * '='}| Finished step |{10 * '='}\n")

    logger.warning(f"Cleaning tmp {repo_dir}")
    os.system(f"rm -rf {repo_dir}")
    logger.removeHandler(file_handler)
logger.info("Exiting")
