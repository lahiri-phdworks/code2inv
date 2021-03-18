import os
import sys

from code2inv.processing.simplifier import getExpr
from code2inv.prog_generator.checkers.c_inv_checker import inv_solver

pwd = os.path.dirname(__file__)
benchmark = os.path.join(pwd, os.pardir, "benchmarks", "C_instances", "c_smt2")

if __name__ == "__main__":
    fileName = sys.argv[1]
    resultFile = fileName.strip().split("/")[-1]
    inv = ""

    if "c_nl_spec" in fileName:
        invType = "c_nl_spec"
        example = resultFile.strip().split("_")[-4]
    elif "c_spec" in fileName:
        invType = "c_spec"
        example = resultFile.strip().split("_")[-3]
    elif "fuzz_spec" in fileName:
        invType = "fuzz_spec"
        example = resultFile.strip().split("_")[-3]
    else:
        pass

    if "inv_result" in fileName:
        converged = "Yes"
    elif "log_inv" in fileName:
        converged = "No"
    else:
        pass

    vc_file = os.path.join(benchmark, f"{example}.c.smt")

    with open(fileName, mode="r") as fileptr:
        lines = fileptr.readlines()

    if len(lines) > 0:
        if "best_root" in lines[0]:
            inv = lines[0].strip().split(":")[1].strip()
        else:
            inv = lines[0].strip()

    res = inv_solver(vc_file, str(inv))

    if res == [None, None, None]:
        check = "Passed"
    else:
        check = "Failed"

    print(
        f'{example}, {invType}, {str(inv)}, {str(check)}, {str(converged)}, "{(getExpr(str(inv)))}"'
    )
