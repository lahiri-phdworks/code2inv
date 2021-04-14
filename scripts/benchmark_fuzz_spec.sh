#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

for TIMEOUT in 10 20;
do
    for EPOCH in 8;
    do
        echo $TIMEOUT -- $EPOCH

        mkdir -p RUNNER_TIME_LOGS RUNNER_LOGS_${TIMEOUT}_${EPOCH}
        mkdir -p results_${TIMEOUT}_${EPOCH}_folder_128
        
        export TIMEOUT=$TIMEOUT
        export EPOCHS=$EPOCH
        
        for file_index in 101 103 104 105 10 116 11 120 128 129 12 133 13 14 15 16 17 19 20 51 54 63 4 41 70 74 77 79 80 83;
        do
            var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
            # if [[ ! ${del_cases[*]} =~ (^|[[:space:]])${var}($|[[:space:]]) ]]; then
            if [[ -n $var ]]; then 

                echo Processing $var.c file
            
                (time ./run_solver_file_mod.sh \
                ../../benchmarks/C_instances/c_graph/${var}.c.json \
                ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_spec \
                -o results_${TIMEOUT}_${EPOCH}_folder_128/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec  \
                $TIMEOUT $EPOCH > RUNNER_LOGS_${TIMEOUT}_${EPOCH}/fuzz_${var}_${TIMEOUT}_${EPOCH}.txt )   \
                2> RUNNER_TIME_LOGS/time_${var}_${TIMEOUT}_${EPOCH}_fuzz_spec.txt
            
                cat RUNNER_TIME_LOGS/time_${var}_${TIMEOUT}_${EPOCH}_fuzz_spec.txt
            fi
            # fi
        done
    done
done