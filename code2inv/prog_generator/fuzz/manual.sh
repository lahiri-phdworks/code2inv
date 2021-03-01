sudo ./afl-init.sh
./start.sh -b build -o output -t tests -e ssum
timeout 20 ./fuzz.sh -b build -o output -t tests -m 10G -e ssum