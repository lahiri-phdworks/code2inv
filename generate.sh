#!/bin/bash

rm -rf /production/benchmarks/C_instances/c_graph/*
rm -rf /production/benchmarks/C_instances/c_smt2/*

for file_index in benchmarks/C_instances/c/*.c;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    if [[ -n $var ]]; then 
        echo Processing file $var.c 
        /code2inv/clang-fe/bin/clang-fe -ssa $file_index > /production/benchmarks/C_instances/c_graph/$var.c.json 2>/dev/null
        /code2inv/clang-fe/bin/clang-fe -smt $file_index > /production/benchmarks/C_instances/c_smt2/$var.c.smt 2>/dev/null
        sleep 0.03
    fi
done

chmod 777 /production/benchmarks/C_instances/c_smt2/*
chmod 777 /production/benchmarks/C_instances/c_graph/*