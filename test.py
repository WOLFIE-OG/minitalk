import subprocess
import os
import time


server = subprocess.Popen("./server")

i = 0
while i != 10:
	client = os.system(f"./client {server.pid} 'This is a test {i}'")
	i += 1
	time.sleep(1)
server.terminate()