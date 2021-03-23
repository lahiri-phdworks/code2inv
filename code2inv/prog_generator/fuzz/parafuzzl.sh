testDir="tests"
outputDir="output"
buildDir="build"

## Running AFL in parallel in background.
for i in $(seq 2 `expr "$(nproc)" - 1`); 
do
    echo "Spawning new para-fuzzer now : fuzzer_0$i"
    sleep 1
    afl-fuzz -S fuzzer_0"$i" -i "$testDir/$1" -o "$outputDir/loopcheck/$1" -m 2G "$buildDir"/loopcheck/$1 >/dev/null 2>&1 &
done

## This is to be done last else
## it hangs up and can't proceed.
## Also show atleast progess of Master.
afl-fuzz -M master_fuzz -i "$testDir/$1" -o "$outputDir/loopcheck/$1" -m 2G "$buildDir"/loopcheck/$1
