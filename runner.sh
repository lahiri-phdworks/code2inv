#!/usr/bin/bash

cd code2inv/prog_generator

if [ -z $1 ]; 
then
    echo "Specify index of file to process"
    echo "Usage ./runner.sh <file_index_to_process> <timeout>"
else
    export INVPROCESSFILE=$1
fi

if [ -z $2 ]; 
then
    AFLTIME=15
    echo "Using AFL default timeout"
else
    AFLTIME=$2
fi

if [ -z $3 ]; 
then
    TORCHTIME=250
    echo "Using TORCH default timeout"
else
    TORCHTIME=$3
fi

# TODO : Choose to automate it later on with full file build
timeout $TORCHTIME ./run_solver_file.sh ../../benchmarks/C_instances/c_graph/${INVPROCESSFILE}.c.json ../../benchmarks/C_instances/c_smt2/${INVPROCESSFILE}.c.smt specs/fuzz_spec -o results/inv_result_${INVPROCESSFILE}.txt

# echo "AFL Fuzz Checker"

# cd checkers/
# python3 fuzzsolve_checker.py $1 $2