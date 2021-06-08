#!/bin/bash

rm -rf /project/benchmarks/C_instances/c_graph/*
rm -rf /project/benchmarks/C_instances/c_smt2/*

# Generate for Z3 {133} Benchmark instances
for file_index in $(ls benchmarks/C_instances/c/ | grep [0-9]);
do 
    if [[ -n $file_index ]]; then 
        echo "Processing files for RQ1 & RQ2 benchmarks : $file_index"
        /code2inv/clang-fe/bin/clang-fe -ssa /project/benchmarks/C_instances/c/$file_index > /project/benchmarks/C_instances/c_graph/$file_index.json 2>/dev/null
        /code2inv/clang-fe/bin/clang-fe -smt /project/benchmarks/C_instances/c/$file_index > /project/benchmarks/C_instances/c_smt2/$file_index.smt 2>/dev/null
    fi
done

# RQ2 Benchmark Examples
for file_index in $(ls benchmarks/C_instances/c/ | grep "bench_");
do 
    if [[ -n $file_index ]]; then 
        echo "Processing files for RQ1 & RQ2 benchmarks : $file_index"
        /code2inv/clang-fe/bin/clang-fe -ssa /project/benchmarks/C_instances/c/$file_index > /project/benchmarks/C_instances/c_graph/$file_index.json 2>/dev/null
        /code2inv/clang-fe/bin/clang-fe -smt /project/benchmarks/C_instances/c/$file_index > /project/benchmarks/C_instances/c_smt2/$file_index.smt 2>/dev/null
    fi
done

/code2inv/clang-fe/bin/clang-fe -ssa /project/benchmarks/C_instances/c/gcd_asm.c > /project/benchmarks/C_instances/c_graph/special_gcd_asm.json 2>/dev/null

chmod 777 /project/benchmarks/C_instances/c_smt2/*
chmod 777 /project/benchmarks/C_instances/c_graph/*