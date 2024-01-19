import subprocess
import os
import psutil


server = subprocess.Popen("./server")

message = ""
if psutil.pid_exists(server.pid):
	while message != "DONE":
		message = input("Message: ")
		client = os.system(f"./client {server.pid} '{message}'")

server.terminate()