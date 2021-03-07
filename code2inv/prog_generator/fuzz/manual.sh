#!/usr/bin/bash

sudo ./afl-init.sh

# Arguments for AFL
export CC=$HOME/afl/afl-gcc
export CXX=$HOME/afl/afl-g++
export AFL=$HOME/afl/afl-fuzz

for file_index in src/type1/*.c;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo $var
    if [[ -n $var ]]; then 
        echo Processing $var.c file.
        ./start.sh -b build -o output -t tests -e $var
        timeout 5 ./fuzz.sh -b build -o output -t tests -m 10G -e $var 
    fi
done

pkill afl
pkill afl-fuzz