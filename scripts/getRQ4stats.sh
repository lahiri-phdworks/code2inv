#!/usr/bin/env bash
>results_final.txt

for TIMEOUT in 5 10 20 30;
do
    for EPOCH in 8 10 12 15;
    do
        folder=$HOME/RQ4_RESULTS/results_${TIMEOUT}_${EPOCH}_folder
        echo Processing "$folder"
        echo "Timeout : ${TIMEOUT}, EPOCH : ${EPOCH}" >> results_final.txt
        
        rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt

        rm -rf ../code2inv/prog_generator/results/*_c_*

        cp -r $HOME/RQ4_RESULTS/results_${TIMEOUT}_${EPOCH}_folder/* ../code2inv/prog_generator/results/
        ../code2inv/prog_generator/results/removeRedundent.sh

        echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Simplified Expression, CE-s Count, Solve-Time" > CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv
        for files in ../code2inv/prog_generator/results/*.txt;
        do
            echo "Processing $files"
            timeout 10 python3 csvgen.py $files >> CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv
        done

        correct=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Passed" | wc -l`
        incorrect=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Failed" | wc -l`

        echo "Correct : $correct" >> results_final.txt
        echo "Incorrect : $incorrect" >> results_final.txt

        rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt
        rm -rf models
        rm -rf ../code2inv/new.smt2
    done
done