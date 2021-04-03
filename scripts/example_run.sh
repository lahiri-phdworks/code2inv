#!/usr/bin/bash

cd ../code2inv/prog_generator
export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

# var=$1;
# 75 83 85 96 99 80 83 85
# 101 102 103 104 105 10 114 115 116 117 11 128 129 12 132 133 13 14 15 16 17 18 19 20 21 22 25 28 29 30 33 34 35 36 37 38 39 
# 3 40 41 42 43 44 45 46 47 48 49 4 50 51 52 53 54 55 56 57 58 59 60 63 64 65 66 67 68 69 71 73 74 76 77 78 79 80 81 82 83 84 85 86 87 91 92 97 98 99

# 1 2 4 5 10 12 13 18 21 23 24 26 30 32 35 37 41 45 51 63 70 75 88 96 120 129 89 83 65 54 51 35 95 100 105 106 116 132 133 38 80 85
# last iter : 96 105 2 4 116 10 12 13 18 21 23 24 120 129 106 132 30 35 37 38 41 51 54 63 65 70 98 80 83 85 88 89 45;

for var in 1 2 4 10 18 23 30 35 41 51 54 63 70 80 85 88 89 96 106 120 129;
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