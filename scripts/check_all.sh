#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator/fuzz

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

TIMEOUT=$1

for file_index in src/*.c;
do
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo  ==== Processing ${var}.c file ====  
    if [[ -n $var ]]; then 
        ./start.sh -b bin -o output -t tests -e $var
    fi
done