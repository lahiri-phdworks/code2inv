import io
import os
import time
import sys
import threading
from subprocess import run, CalledProcessError

pwd = os.path.dirname(__file__)
example = sys.argv[1]
timeout = sys.argv[2]
# check = sys.argv[3]

filepath = os.path.join(pwd, f"include/{example}.h")
fuzzbase = os.path.join(pwd)

premodelsfile = os.path.join(pwd, "premodels.txt")
loopmodelsfile = os.path.join(pwd, "loopmodels.txt")
postmodelsfile = os.path.join(pwd, "postmodels.txt")

files = [premodelsfile, loopmodelsfile, postmodelsfile]
checkList = ["precheck", "loopcheck", "postcheck"]


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


def call_fuzzsolver(index):
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        open(files[index], "w").close()
        output = run(
            f"timeout {timeout} ./fuzz.sh -b ./build -t ./tests \
                -c {checkList[index]} -m 3G -o ./output -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Fuzzer Error : {err}")
    # else:
    #     print(f"Fuzzer Return : {output.returncode}")
    return output.returncode


def init_fuzzbase(index):
    try:
        # print(f"Initialized AFL run on Example {example}.c")
        open(files[index], "w").close()
        output = run(
            f"./start.sh -b ./build -t ./tests -c {checkList[index]} \
                -o ./output -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Build Error : {err}")
    # else:
    #     print(f"Build Return : {output.returncode}")
    return output.returncode


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


if __name__ == "__main__":
    # tqdm.write(f"fuzz-inv solver called : {inv}")
    # dump_template(filepath, inv)

    executeBuildThreads = []
    for i in range(3):
        worker_thread = threading.Thread(
            target=init_fuzzbase, args=(i,))
        executeBuildThreads.append(worker_thread)
        worker_thread.start()

    for index, worker in enumerate(executeBuildThreads):
        worker.join()

    # Side-effect : Delete all contents of the file.
    open(premodelsfile, "w").close()
    open(loopmodelsfile, "w").close()
    open(postmodelsfile, "w").close()

    time.sleep(0.5)

    executeBuildThreads = []
    for i in range(3):
        worker_thread = threading.Thread(
            target=call_fuzzsolver, args=(i,))
        executeBuildThreads.append(worker_thread)
        worker_thread.start()

    for index, worker in enumerate(executeBuildThreads):
        worker.join()

    res = mergeModels()
    print(res)
