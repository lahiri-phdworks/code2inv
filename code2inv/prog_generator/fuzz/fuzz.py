import os
import sys
from subprocess import run, CalledProcessError

pwd = os.path.dirname(__file__)
example = sys.argv[1]
timeout = sys.argv[2]

filepath = os.path.join(pwd, f"include/{example}.h")
fuzzbase = os.path.join(pwd)


def call_fuzzsolver():
    try:
        print(f"Running AFL on Example {example}.c")
        output = run(
            f'timeout {timeout} ./fuzz.sh -b build -t tests -m 10G -o output -e {example}', shell=True, text=True)
    except CalledProcessError as err:
        print(f"Fuzzer Error : {err}")
    else:
        print(f"Return : {output.returncode}")


def init_fuzzbase():
    try:
        print(f"Initialized AFL run on Example {example}.c")
        output = run(
            f'./start.sh -b build -t tests -o output -e {example}', shell=True, text=True)
    except CalledProcessError as err:
        print(f"Build Error : {err}")
    else:
        print(f"Return : {output.returncode}")


if __name__ == '__main__':
    print("Fuzz Solver Raw")
    init_fuzzbase()
    call_fuzzsolver()
