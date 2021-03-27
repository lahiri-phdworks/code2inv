#!/usr/bin/bash

cd ../code2inv/prog_generator
export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

for file_index in fuzz/src/*.c;
do
    sleep 2
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo $var
    if [[ -n $var ]] && [[ $var -ne 32 ]]; then 
        ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_spec \
        -o results/inv_result_${var}_fuzz_spec.txt ${var} fuzz_spec
    fi
done