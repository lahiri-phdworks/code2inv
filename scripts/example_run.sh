#!/usr/bin/bash

cd ../code2inv/prog_generator
export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

# var=$1;

for var in 75 80 83 85 88 89 94 95 96 98 99;
do
    # ./run_solver_file.sh \
    # ../../benchmarks/C_instances/c_graph/${var}.c.json \
    # ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_spec \
    # -o results/inv_result_${var}_c_spec.txt ${var} c_spec

    # ./run_solver_file.sh \
    # ../../benchmarks/C_instances/c_graph/${var}.c.json \
    # ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
    # -o results/inv_result_${var}_c_nl_spec.txt ${var} c_nl_spec

    ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_spec \
    -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec
done