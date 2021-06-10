#!/usr/bin/bash

./dryRun.sh bench_binsearch 10 > binsearch.txt
./dryRun.sh bench_factmodulo 10 > factmodulo.txt
./dryRun.sh bench_gcd_asm 10 > gcd_asm.txt
./dryRun.sh bench_intdiv_simple 10 > intdiv.txt
./dryRun.sh bench_partition 10 > partition.txt
./dryRun.sh bench_exp 10 > exp.txt
./dryRun.sh bench_fibonacci 10 > fibonacci.txt
./dryRun.sh bench_gcd 10 > gcd.txt
./dryRun.sh bench_lcm 10 > lcm.txt
./dryRun.sh bench_sqrt 10 > sqrt.txt