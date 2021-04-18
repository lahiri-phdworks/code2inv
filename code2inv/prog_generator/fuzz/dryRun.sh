#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

example=$1
timeout=$2

echo  ======== Compiling $example ========
./start.sh -b bin -o output -t tests -e $example

echo  ======== Executing $example ========
timeout $timeout ./fuzz.sh -b bin -o output -t tests -e $example
