#!/usr/bin/env bash
set -e
set -u
set -o pipefail

EXAMPLE=$1
SPEC=$2
cd ../code2inv/prog_generator/candidates
file=candidates_${EXAMPLE}_${SPEC}.txt

count=$(cat $file | uniq | wc -l)
items=$(cat $file | uniq | tail -n 1)
echo "$file : $count" # >> getCandidates.log
echo "Expression : $items"

