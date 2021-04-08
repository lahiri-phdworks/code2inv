#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator

mkdir -p RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT} RQ2_FULL_LOGS_${EPOCHS}_${TIMEOUT}

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

# 39 20 22 36 40 61 62 74 77 79 nl-1 nl-1 nl-2 nl-3 nl-4 nl-5 nl-6 nl-7
for var in 39 20 22 36 40 61 62 74 77 79 nl-1 nl-2 nl-3 nl-4 nl-5 nl-6 nl-7;
do
    # (time ./run_solver_file.sh \
    # ../../benchmarks/C_instances/c_graph/${var}.c.json \
    # ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_spec \
    # -o results/inv_result_${var}_c_spec.txt ${var} c_spec > RQ2_FULL_LOGS_${EPOCHS}_${TIMEOUT}/z3_full_${var}.log) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/z3_time_${var}.log

    sleep 1

    (time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
    -o results/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec > RQ2_FULL_LOGS_${EPOCHS}_${TIMEOUT}/z3_nl_full_${var}.log) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/z3_nl_time_${var}.log

    # sleep 1
    
    # (time ./run_solver_file.sh \
    # ../../benchmarks/modified_C/c_graph/${var}.c.json \
    # ../../benchmarks/modified_C/c_smt2/${var}.c.smt specs/fuzz_spec \
    # -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec > RQ2_FULL_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_full_${var}.log) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_time_${var}.log

    # sleep 1

    # (time ./run_solver_file.sh \
    # ../../benchmarks/modified_C/c_graph/${var}.c.json \
    # ../../benchmarks/modified_C/c_smt2/${var}.c.smt specs/fuzz_nl_spec \
    # -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz__nl_spec > RQ2_FULL_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_full_${var}.log) 2> RQ2_TIME_LOGS_${EPOCHS}_${TIMEOUT}/fuzz_time_${var}.log

done
