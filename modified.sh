#!/bin/bash

rm -rf /production/benchmarks/modified_C/c_graph/*
rm -rf /production/benchmarks/modified_C/c_smt2/*

# Get the Pair-1 for Z3 and move to Z3 Benchmark examples.
for file_index in benchmarks/modified_C/orig_c/*.c;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    if [[ -n $var ]]; then 
        echo Processing file original : $var.c 
        /code2inv/clang-fe/bin/clang-fe -ssa $file_index > /production/benchmarks/C_instances/c_graph/$var.c.json 2>/dev/null
        /code2inv/clang-fe/bin/clang-fe -smt $file_index > /production/benchmarks/C_instances/c_smt2/$var.c.smt 2>/dev/null
    fi
done

# Get the Pair-2 for HonggFuzz and move to modifiec_C examples. 
for file_index in benchmarks/modified_C/c/*.c;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    if [[ -n $var ]]; then 
        echo Processing file modified : $var.c 
        /code2inv/clang-fe/bin/clang-fe -ssa $file_index > /production/benchmarks/modified_C/c_graph/$var.c.json 2>/dev/null
        /code2inv/clang-fe/bin/clang-fe -smt $file_index > /production/benchmarks/modified_C/c_smt2/$var.c.smt 2>/dev/null
    fi
done

# for file_index in benchmarks/modified_C/c/*.c;
# do 
#     var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep nl` # grep nl
#     if [[ -n $var ]]; then 
#         echo Processing file $var.c 
#         /code2inv/clang-fe/bin/clang-fe -ssa $file_index > /production/benchmarks/modified_C/c_graph/$var.c.json 2>/dev/null
#         /code2inv/clang-fe/bin/clang-fe -smt $file_index > /production/benchmarks/modified_C/c_smt2/$var.c.smt 2>/dev/null
#         sleep 0.01
#     fi
# done

chmod 755 /production/benchmarks/modified_C/c_smt2/*
chmod 755 /production/benchmarks/modified_C/c_graph/*
chmod 755 /production/benchmarks/C_instances/c_smt2/*
chmod 755 /production/benchmarks/C_instances/c_graph/*