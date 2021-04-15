#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator
mkdir -p RUNNER_TIME_LOGS_Z3 results_Z3

for file_index in 25 31 33 34 42 43 44 46 47 48 49 50 52 53 55 56 57 58 59 60 64 66 67 69 71 72 73 76 78 81 82 84 86 87 90 97 107 111 113 117 118 119 122 123 121 125 131 132; 
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
        -o results_Z3/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec ) 2> RUNNER_TIME_LOGS_Z3/time_${var}_8_z3_nl_spec.txt
    fi
done