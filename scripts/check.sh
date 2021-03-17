#!/usr/bin/bash
model=`python3 code2inv/prog_generator/checkers/c_inv_checker.py benchmarks/C_instances/c_smt2/$1.c.smt "$2"`
simplify=`python3 code2inv/processing/simplifier.py "$2"`

echo "Model : $model"
echo "Simplifed Expression : $simplify"
