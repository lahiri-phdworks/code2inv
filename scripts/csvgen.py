import os
import sys
import json

from code2inv.processing.simplifier import getExpr
from code2inv.prog_generator.checkers.c_inv_checker import inv_solver

pwd = os.path.dirname(__file__)
benchmark = os.path.join(pwd, os.pardir, "benchmarks", "C_instances", "c_smt2")

if __name__ == "__main__":

    resDict = dict()
    instanceObj = dict()
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

    stats = lines[-1].strip().split(":")[-1].strip()[:-2]
    if len(lines) > 0:
        if "best_root" in lines[0]:
            inv = lines[0].strip().split(":")[1].strip()
        else:
            inv = lines[0].strip()

    res = inv_solver(vc_file, str(inv))

    if res == [None, None, None]:
        check = "Passed"
        resDict["status"] = True
    else:
        check = "Failed"
        resDict["status"] = False

    simpleExpr = getExpr(str(inv))
    if isinstance(simpleExpr, list):
        simpleStr = ".".join(x for x in simpleExpr)
    else:
        simpleStr = str(simpleExpr)

    if "c_nl_spec" in fileName:
        resDict["rtime"] = int(stats)
        resDict["type"] = "Z3_C_SPEC"
        instanceObj[f"instance{example}"] = resDict
        with open(os.path.join("scatter", f'z3_c_data.json'), mode="a") as fileptr:
            json.dump(instanceObj, fileptr, indent=4)
            fileptr.write(",\n")
    elif "c_spec" in fileName:
        resDict["rtime"] = int(stats)
        resDict["type"] = "Z3_C_NL_SPEC"
        instanceObj[f"instance{example}"] = resDict
        with open(os.path.join("scatter", f'z3_c_nl_data.json'), mode="a") as fileptr:
            json.dump(instanceObj, fileptr, indent=4)
            fileptr.write(",\n")
    elif "fuzz_spec" in fileName:
        resDict["rtime"] = int(stats)
        resDict["type"] = "FUZZ_SPEC"
        instanceObj[f"instance{example}"] = resDict
        with open(os.path.join("scatter", f'fuzz_nl_data.json'), mode="a") as fileptr:
            json.dump(instanceObj, fileptr, indent=4)
            fileptr.write(",\n")
    else:
        pass

    print(
        f'{example}, {invType}, {str(inv)}, {str(check)}, {str(converged)}, "{simpleStr}", {stats}'
    )
