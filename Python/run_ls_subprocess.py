from subprocess import Popen, PIPE

with Popen(["ls", "-l"], stdout=PIPE, encoding="utf8") as proc:
    for line in proc.stdout:
        print(line.upper())
