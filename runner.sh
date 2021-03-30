set -e
set -u
set -o pipefail

cd code2inv/prog_generator

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

if [ -z $1 ]; 
then
    echo "Specify index of file to process"
    echo "Usage ./runner.sh <file_index_to_process> <spec_type>"
else
    export INVPROCESSFILE=$1
fi

if [ -z $2 ]; 
then
    echo "Specify SPEC"
    echo "Usage ./runner.sh <file_index_to_process> <spec_type>"
else
    export SPEC=$2
fi

./run_solver_file.sh \
../../benchmarks/C_instances/c_graph/${INVPROCESSFILE}.c.json \
../../benchmarks/C_instances/c_smt2/${INVPROCESSFILE}.c.smt specs/$SPEC \
-o results/inv_result_${INVPROCESSFILE}_${SPEC}.txt ${INVPROCESSFILE} $SPEC
