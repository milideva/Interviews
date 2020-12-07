import pexpect


if __name__ == '__main__':

    with pexpect.spawn("telnet 192.168.169.1", encoding="utf8") as telnet:
        telnet.expect("login: ")
        telnet.sendline("hame")

        telnet.expect("Password: ")
        telnet.sendline("hame")

        telnet.expect("# ")
        telnet.sendline("cat /proc/cpuinfo")
        telnet.expect("# ")

        print(telnet.before)
        telnet.sendline("exit")

