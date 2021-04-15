#!/usr/bin/env bash
# set -e
# set -u
# set -o pipefail

TIMEOUT=$1
EPOCH=$2

mkdir -p CSVs

# rm -rf ../code2inv/prog_generator/results/*_c_spec.txt
# cp -r $HOME/RQ4_RESULTS_2/results_${TIMEOUT}_${EPOCH}_folder/* ../code2inv/prog_generator/results/

cp -r ../code2inv/prog_generator/results_${TIMEOUT}_${EPOCH}_folder_extras/* ../code2inv/prog_generator/results/

echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Simplified Expression, CE-s Count, Solve-Time" > CSVs/compile_results_${TIMEOUT}_${EPOCH}_extras.csv
for files in ../code2inv/prog_generator/results/*.txt;
do
    echo "Processing $files"
    timeout 10 python3 csvgen.py $files >> CSVs/compile_results_${TIMEOUT}_${EPOCH}_extras.csv
done

correct=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}_extras.csv | grep "Passed" | grep "Yes" | wc -l`
incorrect=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}_extras.csv | grep "Failed" | grep "Yes" | wc -l`

echo "Correct : $correct"
echo "Incorrect : $incorrect"

rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt
rm -rf models
rm -rf ../code2inv/new.smt2