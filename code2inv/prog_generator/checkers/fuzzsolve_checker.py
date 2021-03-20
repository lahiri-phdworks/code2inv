# Run fuzz solver as subprocess and
# then use it to test the invariants.

# AFL/fuzzsolver module.
from code2inv.prog_generator.checkers.c_inv_checker import inv_solver as c_inv_solver
from code2inv.prog_generator.checkers.c_inv_checker import inv_checker as c_inv_checker
from code2inv.common.constants import AFL_CALLS
from subprocess import run, CalledProcessError
from code2inv.common.cmd_args import cmd_args
from code2inv.prog_generator.chc_tools.chctools.solver_utils import *
from code2inv.prog_generator.chc_tools.chctools.horndb import *
from tqdm import tqdm
from alive_progress import alive_bar
import threading
import io
import os
import time

set_build = False
pwd = os.path.dirname(__file__)

if cmd_args.example:
    example = cmd_args.example
else:
    example = "32"

if cmd_args.example:
    timeout = cmd_args.afl_timeout
else:
    timeout = 10

dump_results = os.path.join(pwd, os.pardir, f"results/log_inv_{example}.txt")
filepath = os.path.join(pwd, os.pardir, f"fuzz/include/{example}.h")
fuzzbase = os.path.join(pwd, os.pardir, f"fuzz")

premodelsfile = os.path.join(pwd, os.pardir, "premodels.txt")
loopmodelsfile = os.path.join(pwd, os.pardir, "loopmodels.txt")
postmodelsfile = os.path.join(pwd, os.pardir, "postmodels.txt")

checkList = ["precheck", "loopcheck", "postcheck"]
modelFilesList = [premodelsfile, loopmodelsfile, postmodelsfile]
fuzzThreadsReturns = [None, None, None]
returncodes = [None, None, None]


def inv_checker(vc_file: str, inv: str, assignments):
    c_inv_checker(vc_file, inv, assignments)


def process_model_string(model: str):
    # COMMENT : iterate over all crashes inputs and extract test failures
    vals = []
    decls = []
    model_val = dict()

    if model == "":
        return None

    cex_type = model.split(":")[0].strip()
    m_list = model.replace(":", ",").split(",")
    for index, elems in enumerate(m_list):
        if (index % 2) == 0:
            vals.append(elems.strip())
        else:
            decls.append(elems.strip())
    vals.pop(0)
    for key, values in zip(decls, vals):
        model_val[f"{key}"] = values
    return [cex_type, model_val]


def call_fuzzsolver(index, time):
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        # COMMENT : Start fresh fuzzing and clean previous model written.
        open(modelFilesList[index], mode="w").close()
        output = run(
            f"timeout {time} {fuzzbase}/fuzz.sh -b {fuzzbase}/build -t {fuzzbase}/tests \
                -c {checkList[index]} -m 3G -o {fuzzbase}/output -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Fuzzer Error : {err}")
    # else:
    #     print(f"Fuzzer Return : {output.returncode}")
    if output.returncode is not 0:
        fuzzThreadsReturns[index] = "EXCEPT"
    returncodes[index] = output.returncode
    return output.returncode


def init_fuzzbase(index):
    try:
        # print(f"Initialized AFL run on Example {example}.c")
        output = run(
            f"{fuzzbase}/start.sh -b {fuzzbase}/build -t {fuzzbase}/tests \
                -c {checkList[index]} -o {fuzzbase}/output -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Build Error : {err}")
    # else:
    #     print(f"Build Return : {output.returncode}")
    return output.returncode


def dump_template(file, inv_code):
    with open(file, mode="w") as fileptr:
        fileptr.write(f"#define PHI {inv_code} // generated by code2inv\n")


def process_crashes(fileName):
    # COMMENT : iterate over all crashes inputs and extract test failures
    results = None
    with open(fileName, mode="r") as fileptr:
        models = fileptr.readlines()
        if len(models) >= 2:
            if "failed" in models[-1].strip():
                results = process_model_string(models[-2].strip())
            else:
                pass
            # tqdm.write(f"{models[-1].strip()}")
    if results is not None:
        return results[1]
    else:
        return None


def mergeModels():
    # TODO : Merge Models here.
    preModel = process_crashes(premodelsfile)
    loopModel = process_crashes(loopmodelsfile)
    postModel = process_crashes(postmodelsfile)
    return [preModel, loopModel, postModel]


def inv_solver(vc_file: str, inv: str):
    # COMMENT : Gets called in each env.step() iteration.
    # COMMENT : None of these functions must fail here.
    # tqdm.write(f"fuzz-inv solver called : {inv}")
    dump_template(filepath, inv)

    executeBuildThreads = []
    for i in range(3):
        worker_thread = threading.Thread(target=init_fuzzbase, args=(i,))
        executeBuildThreads.append(worker_thread)
        worker_thread.start()

    for index, worker in enumerate(executeBuildThreads):
        worker.join()

    # Side-effect : Delete all contents of the file.
    open(premodelsfile, "w").close()
    open(loopmodelsfile, "w").close()
    open(postmodelsfile, "w").close()

    executeBuildThreads = []
    for i in range(3):
        worker_thread = threading.Thread(
            target=call_fuzzsolver, args=(i, timeout, ))
        executeBuildThreads.append(worker_thread)
        worker_thread.start()

    for index, worker in enumerate(executeBuildThreads):
        worker.join()

    res = mergeModels()

    # # COMMENT :
    # # All the three threads timeout so we double the timeout
    # # and check if the INV still holds.
    # if res == [None, None, None]:
    #     timeout *= 2
    #     executeBuildThreads = []
    #     for i in range(3):
    #         worker_thread = threading.Thread(
    #             target=call_fuzzsolver, args=(i, timeout, ))
    #         executeBuildThreads.append(worker_thread)
    #         worker_thread.start()

    #     for index, worker in enumerate(executeBuildThreads):
    #         worker.join()

    # for i in range(3):
    #     if returncodes[i] == 124:
    #         call_fuzzsolver(i, timeout)
    # res = mergeModels()

    # for index, elems in enumerate(res):
    #     if elems is None:
    #         res[index] = fuzzThreadsReturns[index]

    tqdm.write(f"{returncodes} : {res}")
    return res
