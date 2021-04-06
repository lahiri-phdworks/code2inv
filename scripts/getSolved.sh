#!/usr/bin/bash

./compile.sh

correct=`cat compile_results.csv | grep "fuzz_spec" | grep "Passed" | wc -l`
incorrect=`cat compile_results.csv | grep "fuzz_spec" | grep "Failed" | wc -l`

echo "Correct : $correct"
echo "Incorrect : $incorrect"
