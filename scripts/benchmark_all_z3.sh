#!/usr/bin/bash

cd ../code2inv/prog_generator

for file_index in {71..133}
do
    if [[ $file_index -ne 95 ]]
        ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${file_index}.c.json \
        ../../benchmarks/C_instances/c_smt2/${file_index}.c.smt specs/c_spec \
        -o results/inv_result_${file_index}_c_spec.txt ${file_index} c_spec
        
        ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${file_index}.c.json \
        ../../benchmarks/C_instances/c_smt2/${file_index}.c.smt specs/c_nl_spec \
        -o results/inv_result_${file_index}_c_nl_spec.txt ${file_index} c_nl_spec
done