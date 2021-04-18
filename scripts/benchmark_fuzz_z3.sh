#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator
mkdir -p RUNNER_TIME_LOGS_Z3 results_Z3_single

for file_index in 120 2 5 88;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo $var
    if [[ -n $var ]]; then 
        # ( time ./run_solver_file.sh \
        # ../../benchmarks/C_instances/c_graph/${var}.c.json \
        # ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_spec \
        # -o results/inv_result_${var}_c_spec.txt ${var} c_spec ) 2> RUNNER_TIME_LOGS/time_${var}_8_z3_lin_spec.txt
    
        ( time ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
        -o results_Z3_single/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec ) 2> RUNNER_TIME_LOGS_Z3/time_${var}_8_z3_nl_spec.txt
    fi
done