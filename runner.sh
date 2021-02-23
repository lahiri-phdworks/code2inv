#!/usr/bin/bash

cd ./code2inv/prog_generator

if [ -z $1 ]; 
then
    echo "Specify index of file to process"
    echo "Usage ./runner.sh <file_index_to_process> <timeout>"
    exit 1
fi

if [ -z $2 ]; 
then
    echo "Specify afl timeout"
    echo "Usage ./runner.sh <file_index_to_process> <timeout>"
    exit 1
fi

if [ -z $3 ]; 
then
    echo "Specify torch timeout"
    echo "Usage ./runner.sh <file_index_to_process> <timeout>"
    exit 1
fi

export INVPROCESSFILE=$1
timeout $3 ./run_solver_file.sh ../../benchmarks/C_instances/c_graph/${INVPROCESSFILE}.c.json ../../benchmarks/C_instances/c_smt2/${INVPROCESSFILE}.c.smt specs/c_nl_spec -o results/inv_result_${INVPROCESSFILE}.txt

cd checkers/
python3 fuzzsolve_checker.py $1 $2