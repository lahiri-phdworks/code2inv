#!/usr/bin/bash

cd ./code2inv/prog_generator

if [ -z $1 ]; 
then
    echo "Usage ./runner.sh <file_index_to_process>"
    exit 1
fi

export INVPROCESSFILE=$1
./run_solver_file.sh ../../benchmarks/C_instances/c_graph/${INVPROCESSFILE}.c.json ../../benchmarks/C_instances/c_smt2/${INVPROCESSFILE}.c.smt specs/c_nl_spec -o results/inv_result_${INVPROCESSFILE}.txt