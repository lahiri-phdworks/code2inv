#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

export TIMEOUT=$1
export EPOCH=$2

mkdir -p RUNNER_TIME_LOGS
mkdir -p results_${TIMEOUT}_${EPOCH}_folder

for file_index in fuzz/src/*.c;
do

    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo Processing $var file
    sleep 5
        
    if [[ -n $var ]]; then 
        (time ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_spec \
        -o results_${TIMEOUT}_${EPOCH}_folder/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec) 2> RUNNER_TIME_LOGS/time_${var}_fuzz_spec.log
    fi
done