#!/usr/bin/bash

cd code2inv/prog_generator

if [ -z $1 ]; 
then
    echo "Specify index of file to process"
    echo "Usage ./runner.sh <file_index_to_process> <timeout>"
else
    export INVPROCESSFILE=$1
fi

# TODO : Choose to automate it later on with full file build
./run_solver_file.sh ../../benchmarks/C_instances/c_graph/${INVPROCESSFILE}.c.json ../../benchmarks/C_instances/c_smt2/${INVPROCESSFILE}.c.smt specs/$2 -o results/inv_result_${INVPROCESSFILE}.txt ${INVPROCESSFILE} $2

# echo "AFL Fuzz Checker"

# cd checkers/
# python3 fuzzsolve_checker.py $1 $2