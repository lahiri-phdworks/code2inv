#!/usr/bin/env bash
set -e
set -u
set -o pipefail


for file in candidates/*.txt;
do
	count=$(cat $file | uniq | wc -l)
	items=$(cat $file | uniq | tail -n 1)
	echo "$file : $count" >> getCandidates.log
	echo "Expression : $items"
done
