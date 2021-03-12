#!/usr/bin/env bash
set -e
set -u
set -o pipefail

# Usage Prompt
usagePrompt() {
    echo "Usage: ./start.sh [-b] <build_dir> [-o] <output_dir> [-t] <test_dir> [-e] <EXAMPLE CODE>"
}

# Arguments for running specific file
export CC=$HOME/afl/afl-gcc
export CXX=$HOME/afl/afl-g++
export AFL=$HOME/afl/afl-fuzz

while getopts "b:o:t:e:c:" flag; do
  case "$flag" in
    b ) 
        buildDir=$OPTARG
        ;;
    o ) 
        outputDir=$OPTARG
        ;;
    t ) 
        testDir=$OPTARG
        ;;
    e ) 
        RUNNER=$OPTARG
        ;;
    c ) 
        CHECK=$OPTARG
        ;;
    \? ) 
        usagePrompt
        exit 1
        ;;
    : )
        echo "Invalid Option: -$OPTARG requires an argument" 1>&2
        exit 1
        ;;
  esac
done
shift $((OPTIND -1))    

export RUNNER=$RUNNER
export CHECK=$CHECK

rm -rf build/$CHECK/* output/$CHECK/* graph/$CHECK/*

if [ $OPTIND -eq 1 ]; 
    then 
        usagePrompt
        exit 1 
fi

# Build Directory
mkdir -p "$buildDir/$CHECK" 

# Start Build
cd "$buildDir/$CHECK"
CC=$CC CXX=$CXX cmake -DCMAKE_CXX_FLAGS="-w" ../../
make -j 12
cd ../../

# Output Directory
mkdir -p "$outputDir/$CHECK/$RUNNER" 