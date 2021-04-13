#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator

for file_index in fuzz/src/*.c;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo $var
    if [[ -n $var ]]; then 
        ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_spec \
        -o results/inv_result_${var}_c_spec.txt ${var} c_spec
        
        sleep 1

        ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
        -o results/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec
    fi
done