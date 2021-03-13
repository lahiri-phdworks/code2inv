#!/usr/bin/python3

import z3
import sys
from subprocess import run, CalledProcessError
from z3 import *

pwd = os.path.dirname(__file__)
filePath = os.path.join(pwd, os.pardir, f"new.smt2")
parser = os.path.join(pwd, f"parser.py")
inv = sys.argv[1]


def call_ToSmt(inv):
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        output = run(
            f'python3 {parser} "{inv}" > {filePath}',
            shell=True, capture_output=True, text=True)
    except CalledProcessError as err:
        print(f"Simplify Run Error : {err}")
    # else:
    #     print(f"Fuzzer Return : {output.returncode}")
    return output.returncode


def getExpr(inv):
    call_ToSmt(inv)
    f = z3.parse_smt2_file(filePath)
    simplifyTactic = Tactic('simplify')
    for expr in f:
        return simplifyTactic(expr)[0]


if __name__ == '__main__':
    ret = getExpr(inv)
    if len(ret) > 0:
        print(ret[0])
    else:
        print(ret)
