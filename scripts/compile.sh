#!/usr/bin/bash

echo "Example, Type, Invariant, Failure, Simplify Expression" > compile_results.csv
for files in ../code2inv/prog_generator/results/*.txt;
do
    python3 parse.py $files >> compile_results.csv
done