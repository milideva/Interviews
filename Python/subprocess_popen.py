from subprocess import Popen
from time import sleep

with Popen("./slow_script.sh") as p:
    print(f"Process launched: {p=}, {p.pid=}")

    for i in range(5):
        print("Python program: counting", i)
        sleep(1)
    p.kill()

print(f"Process {p.pid} complete")
