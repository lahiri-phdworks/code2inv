#!/usr/bin/env bash
set -e
set -u
set -o pipefail

EPOCHS=$1
TIMEOUT=$2
cd ../code2inv/prog_generator
mkdir -p RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

# 39 20 22 36 40 61 62 74 77 79
for var in 39 20 22 36 40 61 62 74 77 79;
do
    (time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_spec \
    -o results/inv_result_${var}_c_spec.txt ${var} c_spec) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/z3_time_${var}.log

    sleep 1

    (time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
    -o results/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/z3_nl_time_${var}.log

    sleep 1
    
    (time ./run_solver_file.sh \
    ../../benchmarks/modified_C/c_graph/${var}.c.json \
    ../../benchmarks/modified_C/c_smt2/${var}.c.smt specs/fuzz_spec \
    -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_time_${var}.log

    sleep 1

    # (time ./run_solver_file.sh \
    # ../../benchmarks/modified_C/c_graph/${var}.c.json \
    # ../../benchmarks/modified_C/c_smt2/${var}.c.smt specs/fuzz_nl_spec \
    # -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz__nl_spec) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_func_time_${var}.log

done

(time ./run_solver_file.sh \
../../benchmarks/modified_C/c_graph/77.c.json \
../../benchmarks/modified_C/c_smt2/77.c.smt specs/fuzz_nl_spec \
-o results/inv_result_77_fuzz_spec.txt 77 fuzz_nl_spec) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_func_time_77.log