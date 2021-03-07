#!/usr/bin/bash

sudo ./afl-init.sh

# Arguments for AFL
export CC=$HOME/afl/afl-gcc
export CXX=$HOME/afl/afl-g++
export AFL=$HOME/afl/afl-fuzz

./start.sh -b build -o output -t tests -e $1
timeout 10 ./fuzz.sh -b build -o output -t tests -m 10G -e $1