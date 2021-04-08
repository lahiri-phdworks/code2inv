#!/usr/bin/env bash
set -e
set -u
set -o pipefail

clear 

var=$1
echo "Generating for modified $var SMT & SSA-Graphs (JSON)"

rm -rf /production/benchmarks/modified_C/c_graph/$var.c.json
rm -rf /production/benchmarks/modified_C/c_smt2/$var.c.smt

/code2inv/clang-fe/bin/clang-fe -ssa /production/benchmarks/modified_C/c/$var.c > /production/benchmarks/modified_C/c_graph/$var.c.json 2>/dev/null
/code2inv/clang-fe/bin/clang-fe -smt /production/benchmarks/modified_C/c/$var.c > /production/benchmarks/modified_C/c_smt2/$var.c.smt 2>/dev/null

chmod 777 /production/benchmarks/modified_C/c_smt2/*
chmod 777 /production/benchmarks/modified_C/c_graph/*