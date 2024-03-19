# minitalk

The purpose of this project is to code a small data exchange program using UNIX signals. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.

## State

[![minitalk Build](https://img.shields.io/github/actions/workflow/status/WOLFIE-OG/minitalk/makefile.yml?style=for-the-badge)](https://github.com/WOLFIE-OG/minitalk/actions/workflows/makefile.yml) ![minitalk Score](https://img.shields.io/badge/Score-125%2F125-brightgreen?style=for-the-badge)

## Installation & Building

To install and build

```bash
  git clone https://github.com/WOLFIE-OG/minitalk
  cd minitalk
  git submodule update --init --recursive
  make
  ./server
  ./client PID MESSAGE
```
