# Run fuzz solver as subprocess and
# then use it to test the invariants.

# AFL/fuzzsolver module.
import io
import os
import tokenize
from tqdm import tqdm
from code2inv.prog_generator.chc_tools.chctools.horndb import *
from code2inv.prog_generator.chc_tools.chctools.solver_utils import *
from code2inv.common.cmd_args import cmd_args
from subprocess import run, CalledProcessError
from code2inv.common.constants import AFL_CALLS

set_build = False
pwd = os.path.dirname(__file__)

if cmd_args.example:
    example = cmd_args.example
else:
    example = "ssum"

if cmd_args.example:
    timeout = cmd_args.afl_timeout
else:
    timeout = 5

dump_results = os.path.join(pwd, os.pardir, f"results/log_inv_{example}.txt")
filepath = os.path.join(pwd, os.pardir, f"fuzz/include/{example}.h")
fuzzbase = os.path.join(pwd, os.pardir, f"fuzz")
modelsfile = os.path.join(pwd, os.pardir, "models.txt")


def inv_checker(vc_file: str, inv: str, assignments):
    # COMMENT : Same as for c_inv_checker file.
    # assignments come from counter example model that we get from fuzzing.
    inv = inv.replace("&&", "and", -1)
    inv = inv.replace("||", "or", -1)
    b = io.StringIO(inv)
    t = tokenize.generate_tokens(b.readline)
    inv_tokenized = []
    for a in t:
        if a.string != "":
            inv_tokenized.append(a.string)

    var_list = set()
    for token in inv_tokenized:
        if token[0] in "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" and token not in ("and", "or"):
            var_list.add(token)

    for assignment in assignments:
        v = assignment[0]
        val = assignment[1]
        if v in var_list:
            exec(v + "=" + str(val))
            var_list.discard(v)

    for var in var_list:
        exec(var + "=1")

    try:
        return eval(inv)
    except:
        return False


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
        model_val[f"{key}"] = int(values)
    return [cex_type, model_val]


def call_fuzzsolver():
    # TODO : Get counter example model out of afl "crash" case.
    # TODO : Try out for "ssum" case and then extract model for counter examples here.
    try:
        # print(f"Running AFL on Example {example}.c")
        output = run(
            f'timeout {timeout} {fuzzbase}/fuzz.sh -b {fuzzbase}/build -t {fuzzbase}/tests -m 10G -o {fuzzbase}/output -e {example}',
            shell=True, capture_output=True, text=True)
    except CalledProcessError as err:
        print(f"Fuzzer Error : {err}")
    # else:
    #     print(f"Fuzzer Return : {output.returncode}")
    return output.returncode


def init_fuzzbase():
    try:
        # print(f"Initialized AFL run on Example {example}.c")
        output = run(
            f'{fuzzbase}/start.sh -b {fuzzbase}/build -t {fuzzbase}/tests -o {fuzzbase}/output -e {example}',
            shell=True, capture_output=True, text=True)
    except CalledProcessError as err:
        print(f"Build Error : {err}")
    # else:
    #     print(f"Build Return : {output.returncode}")
    return output.returncode


def dump_template(file, inv_code):
    with open(file, mode="w") as fileptr:
        fileptr.write(f"#define PHI {inv_code} // generated by code2inv\n")


def process_crashes():
    # COMMENT : iterate over all crashes inputs and extract test failures
    with open(modelsfile, mode="r") as fileptr:
        models = fileptr.readlines()
        if models is not None and "failed" in models[-1].strip():
            results = process_model_string(models[-2].strip())
            tqdm.write(f"{models[-1]}")
    if results is not None:
        if results[0] == "Pre":
            return [results[1], None, None]
        elif results[0] == "Post":
            return [None, None, results[1]]
        else:
            return [None, results[1], None]
    else:
        return [None, None, None]


def inv_solver(vc_file: str, inv: str):
    # COMMENT : Gets called in each env.step() iteration.
    # COMMENT : None of these functions must fail here.
    # tqdm.write(f"fuzz-inv solver called : {inv}")

    dump_template(filepath, inv)
    init_fuzzbase()
    call_fuzzsolver()
    res = process_crashes()
    # tqdm.write(f"{res}")
    return res
