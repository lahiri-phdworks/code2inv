#!/usr/bin/env bash
>results_final.txt

for EPOCH in 8 10 12 15;
do
    arr=()
    percents=()
    for TIMEOUT in 5 10 20 30;
    do
        folder=$HOME/DUMP/results_${TIMEOUT}_${EPOCH}_folder
        echo Processing "$folder"
        echo "Timeout : ${TIMEOUT}, EPOCH : ${EPOCH}" >> results_final.txt
        
        rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt
        # rm -rf ../code2inv/prog_generator/results/*_c_*

        cp -r $HOME/DUMP/results_${TIMEOUT}_${EPOCH}_folder/* ../code2inv/prog_generator/results/
        ../code2inv/prog_generator/results/removeRedundent.sh

        echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Simplified Expression, CE-s Count, Solve-Time" > CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv
        for files in ../code2inv/prog_generator/results/*.txt;
        do
            echo "Processing $files"
            timeout 10 python3 csvgen.py $files >> CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv
        done

        converged=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Yes" | wc -l`
        correct=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Passed" | wc -l`
        incorrect=`cat CSVs/compile_results_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Failed" | wc -l`
        percent=`echo "scale=2; $correct * 100 / $converged " | bc -l`

        echo "Correct : $correct" >> results_final.txt
        echo "Incorrect : $incorrect" >> results_final.txt
        echo "Converged : $converged" >> results_final.txt
        echo "Percent Correct : $percent" >> results_final.txt
        echo "" >> results_final.txt

        arr+=($correct)
        percents+=($percent)

        rm -rf ../code2inv/prog_generator/results/*_fuzz_spec.txt
        rm -rf models
        rm -rf ../code2inv/new.smt2
    done
    printf "[" >> results_final.txt
    printf '%s, ' "${arr[@]}" >> results_final.txt
    printf "]\n    ----    " >> results_final.txt
    printf "\n[" >> results_final.txt
    printf '%s, ' "${percents[@]}" >> results_final.txt
    printf "]\n    ----    " >> results_final.txt
    echo "" >> results_final.txt
done