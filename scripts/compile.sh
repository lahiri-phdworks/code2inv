#!/usr/bin/bash

echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Z3 Simplify Expression" > compile_results.csv
for files in ../code2inv/prog_generator/results/*.txt;
do
    python3 parse.py $files >> compile_results.csv
done

cat compile_results.csv | grep c_