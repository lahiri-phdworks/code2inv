import io
import os
import time
import sys
import threading
from subprocess import run, CalledProcessError

pwd = os.path.dirname(__file__)
example = sys.argv[1]
timeout = sys.argv[2]

filepath = os.path.join(pwd, f"include/{example}.h")
fuzzbase = os.path.join(pwd)
outputFile = os.path.join(pwd, "models.txt")
collection_semantic = [None, None, None]

# premodelsfile = os.path.join(pwd, "premodels.txt")
# loopmodelsfile = os.path.join(pwd, "loopmodels.txt")
# postmodelsfile = os.path.join(pwd, "postmodels.txt")

# checkList = ["precheck", "loopcheck", "postcheck"]
# modelFilesList = [premodelsfile, loopmodelsfile, postmodelsfile]
# fuzzThreadsReturns = [None, None, None]
# returncodes = [None, None, None]


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


def call_fuzzsolver(time):
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        # COMMENT : Start fresh fuzzing and clean previous model written.
        output = run(
            f"timeout {time} ./fuzz.sh -b ./bin -o ./output -t ./tests -e {example}",
            shell=True,
            capture_output=True,
            text=True,
        )
    except CalledProcessError as err:
        print(f"Fuzzer Error : {err}")
    # else:
    #     print(f"Fuzzer Return : {output.returncode}")
    return output.returncode


def init_fuzzbase():
    # TODO : Now we have to make three parallel calls for pre, loop and post as per new sampling technique.
    try:
        # print(f"Running AFL on Example {example}.c")
        # COMMENT : Start fresh fuzzing and clean previous model written.
        output = run(
            f"./start.sh -b ./bin/ -o ./output/ -t ./tests/ -e {example}",
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
        if isinstance(models, list) and len(models) > 0:
            for lines in models:
                if "Pre :" in lines:
                    collection_semantic[0] = lines.strip()
                if "Loop :" in lines:
                    collection_semantic[1] = lines.strip()
                if "Post :" in lines:
                    collection_semantic[2] = lines.strip()
        else:
            return None


def mergeModels():
    results = []
    if all(x is None for x in collection_semantic):
        return collection_semantic
    for x in collection_semantic:
        if x is not None:
            results.append(process_model_string(x)[1])
        else:
            results.append(None)

    return results


if __name__ == '__main__':
    # tqdm.write(f"fuzz-inv solver called : {inv}")
    # dump_template(filepath, inv)
    init_fuzzbase()
    call_fuzzsolver(timeout)
    process_crashes(outputFile)
    res = mergeModels()
    print(res)
