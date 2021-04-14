#!/usr/bin/bash
> failed.log
for files in CSVs/*;
do
  cat $files | grep "fuzz_spec" | grep "Failed" | grep "Yes" >> failed.log
done