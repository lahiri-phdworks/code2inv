#!/usr/bin/env bash
set -e
set -u
set -o pipefail

TIMEOUT=$1
EPOCHS=$2

mkdir -p CSVs
rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt
cp -r $HOME/DUMP/results_${TIMEOUT}_${EPOCHS}_folder/* ../code2inv/prog_generator/results/

echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Simplified Expression, CE-s Count, Solve-Time" > CSVs/compile_results_${TIMEOUT}_${EPOCHS}.csv
for files in ../code2inv/prog_generator/results/*.txt;
do
    echo "Processing $files"
    timeout 10 python3 csvgen.py $files >> CSVs/compile_results_${TIMEOUT}_${EPOCHS}.csv
done

correct=`cat CSVs/compile_results_${TIMEOUT}_${EPOCHS}.csv | grep "fuzz_spec" | grep "Passed" | wc -l`
incorrect=`cat CSVs/compile_results_${TIMEOUT}_${EPOCHS}.csv | grep "fuzz_spec" | grep "Failed" | wc -l`

echo "Correct : $correct"
echo "Incorrect : $incorrect"

rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt
rm -rf models
rm -rf ../code2inv/new.smt2