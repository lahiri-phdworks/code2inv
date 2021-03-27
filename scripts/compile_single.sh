#!/usr/bin/bash

echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Z3 Simplify Expression, CE-s Count" > compile_$1.csv
files="../code2inv/prog_generator/results/$1.txt"    
echo "Processing $files"
timeout 10 python3 csvgen.py $files >> compile_$1.csv