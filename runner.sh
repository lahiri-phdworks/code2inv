set -e
set -u
set -o pipefail

cd code2inv/prog_generator

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

mkdir -p RUNNER_TIME_LOGS

if [ -z $1 ]; 
then
    echo "Specify index of file to process"
    echo "Usage ./runner.sh <file_index_to_process> <spec_type>"
else
    export INVPROCESSFILE=$1
    export EXAMPLE=$1
    var=$1
fi

if [ -z $2 ]; 
then
    echo "Specify SPEC"
    echo "Usage ./runner.sh <file_index_to_process> <spec_type>"
else
    export SPEC=$2
fi

(time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/$SPEC \
    -o results_runner/inv_result_${var}_${SPEC}.txt ${var} $SPEC ) 2> RUNNER_TIME_LOGS/time_${var}_${SPEC}.log
