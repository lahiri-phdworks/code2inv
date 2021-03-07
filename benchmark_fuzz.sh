#!/usr/bin/bash

cd code2inv/prog_generator

for file_index in 1 2 5 10 13 18 21 75 98 ssum;
do
    ./run_solver_file.sh ../../benchmarks/C_instances/c_graph/${file_index}.c.json ../../benchmarks/C_instances/c_smt2/${file_index}.c.smt specs/fuzz_spec -o results/inv_result_${file_index}.txt ${file_index} fuzz_spec
done