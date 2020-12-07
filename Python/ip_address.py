from subprocess import Popen, PIPE
import platform

def get_ip_addr_macos_simple():
    with Popen(["/sbin/ifconfig"], stdout=PIPE, encoding="utf8") as proc:
        for line in proc.stdout:
            if "inet " in line:
                print(line.split()[1])


def get_ip_addr_macos():
    with Popen(["/sbin/ifconfig"], stdout=PIPE, encoding="utf8") as proc:
        ip_addrs = [ line.split()[1] for line in proc.stdout if "inet " in line ]
    return ip_addrs

def get_ip_addr_windows():
    with Popen("ipconfig", stdout=PIPE, encoding="utf8") as proc:
        ip_addrs = [ line.split()[-1] for line in proc.stdout if "IPv4" in line ]
    return ip_addrs

def get_ip_addr_linux():
    with Popen(["ip", "addr", "show"], stdout=PIPE, encoding="utf8") as proc:
        ip_addrs = [line.split()[1].split("/")[0] for line in proc.stdout if "inet " in line]
    return ip_addrs

def get_ip_addr_unknown():
    return ["Unknown platform"]

def get_ip_addr_regex():
    import re
    ipv4_pattern = re.compile("\d{1,3}(\.\d{1,3}){3}")
    with Popen("/sbin/ifconfig", stdout=PIPE, encoding="utf8") as proc:
        for line in proc.stdout:
            for match in ipv4_pattern.finditer(line):
                yield match.group()

command = {
    "Darwin": get_ip_addr_macos,
    "Windows": get_ip_addr_windows,
    "Linux": get_ip_addr_linux
}

if __name__ == '__main__':
    for ip in command.get(platform.system(), get_ip_addr_unknown)():
        print(ip)
