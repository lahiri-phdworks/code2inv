#!/usr/bin/bash

cd ./results
./removeRedundent.sh
rm -rf *_fuzz_spec.txt

cd ../
rm -rf RUNNER_TIME_LOGS
rm -rf *.txt *.TXT *.fuzz

# rm -rf fuzz/bin/*
# rm -rf fuzz/*.txt
# rm -rf fuzz/output

