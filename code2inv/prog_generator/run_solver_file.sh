#!/bin/bash

# if(( !($# == 5 || $# == 3) ))
# then
#     echo "Usage- run_solver.sh <input_graph> <input_vcs> <grammar_file> [ -o <output file> ]"
#     exit
# elif [ $# -eq 5 ] && [ "$4" != "-o" ]
# then
#     echo "Usage- run_solver.sh <input_graph> <input_vcs> <grammar_file> [ -o <output file> ]"
#     exit
# fi

data_folder=../../benchmarks
file_list=names.txt

op_file="$5"
echo OP_FILE $op_file
inv_reward_type=ordered
input_graph="$1"
input_vcs="$2"
grammar_file="$3"
example="$6"
specs="$7"
rl_batchsize=10
embedding=128
s2v_level=20
model=AssertAwareTreeLSTM
att=1
ac=0
ce=1
afl_timeout=32
save_dir=$HOME/scratch/results/code2inv/benchmarks/

if [ ! -e $save_dir ];
then
    mkdir -p $save_dir
fi

mkdir -p tests/results

log_file=$save_dir/log-sample-${single_sample}-model-${model}-${ctx}-r-${inv_reward_type}-s2v-${s2v_level}-bsize-${rl_batchsize}-att-${att}-ac-${ac}-ce-${ce}.txt

# COMMENT : Z3 used for this flag

python -u file_solver.py \
    -input_graph $input_graph\
    -input_vcs $input_vcs\
    -exit_on_find 1 \
    -attention $att \
    -use_ce $ce \
    -aggressive_check $ac \
    -encoder_model "Param"\
    -decoder_model $model \
    -only_use_z3 1 \
    -num_epochs 10 \
    -s2v_level $s2v_level \
    -embedding_size $embedding \
    -rl_batchsize $rl_batchsize \
    -inv_reward_type $inv_reward_type \
    -op_file "$op_file" \
    -afl_timeout $afl_timeout \
    -example $example \
    -spec_type $specs \
    -inv_grammar $(sed "1q;d" $grammar_file) \
    -inv_checker $(sed "2q;d" $grammar_file) \
    -var_format "$(sed '3q;d' $grammar_file)"\
    -ctx gpu \
    2>&1 | tee $log_file
