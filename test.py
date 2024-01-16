import subprocess
import os
import random


server = subprocess.Popen("./server")

i = 0
while i != 300:
	client = os.system(f"./client {server.pid} '{i}'")
	i += 1