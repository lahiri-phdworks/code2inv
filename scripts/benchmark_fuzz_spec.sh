#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

must_pass=(11 12 133 13 16 17 18 19 38 40 41 98 99 9 15 41 65 70 77 83 116 28 68 10 88 63)

for TIMEOUT in 10 20;
do
    for EPOCH in 8;
    do
        echo $TIMEOUT -- $EPOCH

        mkdir -p RUNNER_TIME_LOGS RUNNER_LOGS_${TIMEOUT}_${EPOCH}
        mkdir -p results_${TIMEOUT}_${EPOCH}_folder_32
        
        export TIMEOUT=$TIMEOUT
        export EPOCHS=$EPOCH
        
        for file_index in fuzz/src/*.c;
        do
            var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
            # if [[ ! ${del_cases[*]} =~ (^|[[:space:]])${var}($|[[:space:]]) ]]; then
            if [[ -n $var ]]; then 

                echo Processing $var.c file
            
                (time ./run_solver_file_mod.sh \
                ../../benchmarks/C_instances/c_graph/${var}.c.json \
                ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_spec \
                -o results_${TIMEOUT}_${EPOCH}_folder_32/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec $TIMEOUT $EPOCH > RUNNER_LOGS_${TIMEOUT}_${EPOCH}/fuzz_${var}_${TIMEOUT}_${EPOCH}.txt ) 2> RUNNER_TIME_LOGS/time_${var}_${TIMEOUT}_${EPOCH}_fuzz_spec.txt
            
                cat RUNNER_TIME_LOGS/time_${var}_${TIMEOUT}_${EPOCH}_fuzz_spec.txt
            fi
            # fi
        done
    done
done