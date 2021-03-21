#!/usr/bin/env bash
set -e
set -u
set -o pipefail

# Usage Prompt
usagePrompt() {
    echo "Usage: ./fuzz.sh [-b] <build_dir> [-o] <output_dir> [-t] <test_dir> [-e] <EXAMPLE CODE>"
}

# Arguments for running specific file
export CC=$HOME/afl/afl-gcc
export CXX=$HOME/afl/afl-g++
export AFL=$HOME/afl/afl-fuzz

while getopts "b:o:t:e:m:c:" flag; do
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
    m ) 
        MEMORY=$OPTARG
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

# Test Directory
if [[ ! -d $testDir/$RUNNER ]]; then
    echo "Test : $testDir not found !!" 1>&2
fi

file="models.txt"
> $file
$AFL -i "$testDir/$RUNNER" -o "$outputDir/$CHECK/$RUNNER" -m $MEMORY "$buildDir/$CHECK/$RUNNER" "$file"
