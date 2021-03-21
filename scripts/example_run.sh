#!/usr/bin/bash

cd ../code2inv/prog_generator
sudo fuzz/afl-init.sh

# Arguments for AFL
export CC=$HOME/afl/afl-gcc
export CXX=$HOME/afl/afl-g++
export AFL=$HOME/afl/afl-fuzz

var=$1;

for var in 1 2 4 5 37 18 21 24 26 30 32 63 65 68 70 83 85 88 89 94 95 96 98 99 100 105 104 106;
do
    ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_spec \
    -o results/inv_result_${var}_c_spec.txt ${var} c_spec

    ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
    -o results/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec

    # ./run_solver_file.sh \
    # ../../benchmarks/C_instances/c_graph/${var}.c.json \
    # ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_spec \
    # -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec
done