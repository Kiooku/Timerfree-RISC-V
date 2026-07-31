#!/bin/bash

number_of_loop=$1
program_to_execute=$2

if [ $# -ne 2 ]; then
        echo -e "Error: Not enough or too much arguments supplied\nShould look like that: ./run_mutiple_time.sh number_of_loop program_to_execute\n- number_of_loop: Number of time you want to execute your algorithm;\n- program_to_execute: The C code that you want to monitor."
        exit 1
fi

for ((i=1; i<=number_of_loop; i++)); do
    $program_to_execute
done
