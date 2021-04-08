#!/usr/bin/env bash
set -e
set -u
set -o pipefail

clear 

var=$1
echo "Generating for original $var SMT & SSA-Graphs (JSON)"

rm -rf /production/benchmarks/modified_C/c_graph/$var.c.json
rm -rf /production/benchmarks/modified_C/c_smt2/$var.c.smt

/code2inv/clang-fe/bin/clang-fe -ssa /production/benchmarks/modified_C/orig_c/$var.c > /production/benchmarks/modified_C/c_graph/$var.c.json 2>/dev/null
/code2inv/clang-fe/bin/clang-fe -smt /production/benchmarks/modified_C/orig_c/$var.c > /production/benchmarks/modified_C/c_smt2/$var.c.smt 2>/dev/null

chmod 777 /production/benchmarks/modified_C/c_smt2/*
chmod 777 /production/benchmarks/modified_C/c_graph/*

sleep 0.5 

echo "Moving $var files SMT & SSA-Graphs (JSON) to /production/benchmarks/C_instances/c_graph/$var.c*"

mv /production/benchmarks/modified_C/c_graph/$var.c.json /production/benchmarks/C_instances/c_graph/$var.c.json
mv /production/benchmarks/modified_C/c_smt2/$var.c.smt /production/benchmarks/C_instances/c_smt2/$var.c.smt