#!/usr/bin/env bash
# 2 4 8 16 32 64
for EPOCH in 8;
do
    arr=()
    percents=()
    for TIMEOUT in 10;
    do
        for KINDUCTION in 1;
        do
            echo "Timeout : ${TIMEOUT}, EPOCH : ${EPOCH}" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
            echo "Benchmark Example, Type, Invariant, Z3 Check Pass, Code2Inv Converged, Simplified Expression, CE-s Count, Solve-Time" > CSVs/compile_results_${KINDUCTION}_${TIMEOUT}_${EPOCH}.csv
            for files in data/results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_folder_extra/*;
            do
                echo "Processing $files"
                python3 csvgen.py $files >> CSVs/compile_results_${KINDUCTION}_${TIMEOUT}_${EPOCH}.csv
            done

            converged=`cat CSVs/compile_results_${KINDUCTION}_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Yes" | wc -l`
            correct=`cat CSVs/compile_results_${KINDUCTION}_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Passed" | wc -l`
            incorrect=`cat CSVs/compile_results_${KINDUCTION}_${TIMEOUT}_${EPOCH}.csv | grep "fuzz_spec" | grep "Failed" | wc -l`
            percent=`echo "scale=2; $correct * 100 / $converged " | bc -l`

            echo "Correct : $correct" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
            echo "Incorrect : $incorrect" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
            echo "Converged : $converged" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
            echo "Percent Correct : $percent" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
            echo "" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt

            arr+=($correct)
            percents+=($percent)

        done
    done
    printf "[" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
    printf '%s, ' "${arr[@]}" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
    printf "]\n    ----    " >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
    printf "\n[" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
    printf '%s, ' "${percents[@]}" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
    printf "]\n    ----    " >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
    echo "" >> results_${KINDUCTION}_${TIMEOUT}_${EPOCH}_final.txt
done
