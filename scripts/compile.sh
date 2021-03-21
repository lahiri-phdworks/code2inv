#!/usr/bin/bash

echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Z3 Simplify Expression, CE-s Count" > compile_results.csv
for files in ../code2inv/prog_generator/results/*.txt;
do
    echo "Processing $files"
    timeout 10 python3 csvgen.py $files >> compile_results.csv
done