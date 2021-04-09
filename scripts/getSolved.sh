#!/usr/bin/env bash
set -e
set -u
set -o pipefail

echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Z3 Simplify Expression, CE-s Count, Solve-Time" > compile_results.csv
for files in ../code2inv/prog_generator/results/*.txt;
do
    echo "Processing $files"
    timeout 10 python3 csvgen.py $files >> compile_results.csv
done

correct=`cat compile_results.csv | grep "fuzz_spec" | grep "Passed" | wc -l`
incorrect=`cat compile_results.csv | grep "fuzz_spec" | grep "Failed" | wc -l`

echo "Correct : $correct"
echo "Incorrect : $incorrect"
