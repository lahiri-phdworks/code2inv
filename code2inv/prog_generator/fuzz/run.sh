#!/usr/bin/bash

sudo ./afl-init.sh

# Arguments for AFL
export CC=$HOME/afl/afl-gcc
export CXX=$HOME/afl/afl-g++
export AFL=$HOME/afl/afl-fuzz

for file_index in src/loopcheck/*.c;
do 
    var=`echo $file_index |  tr "/" "\n" | tr "." "\n" | grep ^[0-9]`
    echo Processing $var
    if [[ -n $var ]]; then 
        python3 fuzz.py $var 5 
    fi
done

pkill afl
pkill afl-fuzz