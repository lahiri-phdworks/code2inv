#!/usr/bin/bash

for index in {1..133};
do 
    for type in _c_nl_spec _c_spec _fuzz_spec;
    do
        if [[ -f inv_result_$index$type.txt ]];
        then
            if [[ -f log_inv_$index$type.txt ]];
            then
                echo "Redundent File : log_inv_$index$type.txt ! Removing ..."
                rm -rf log_inv_$index$type.txt
            fi
        fi
    done
done