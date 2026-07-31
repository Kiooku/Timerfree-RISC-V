#!/bin/bash

number_of_loop=$1
program_to_execute=$2
path_run_multiple_time=$3
benchmark_name=$4

if [ $# -ne 4 ]; then
        echo -e "Error: Not enough or too much arguments supplied\nShould look like that: ./create_benchmark_detection.sh number_of_loop program_to_execute path_run_multiple_time benchmark_name\n- number_of_loop: Number of time you want to execute your algorithm;\n- program_to_execute: The C code that you want to monitor;\n- path_run_multiple_time: path to run_multiple_time.sh (e.g., ../run_multiple_time.sh) \n- benchmark_name: name of the benchmark file."
        exit 1
fi

mkdir -p $benchmark_name
cd $benchmark_name
../$path_run_multiple_time 50 ../$program_to_execute >> temp.txt
cat temp.txt | grep fileclose | awk 'NR % 2 == 0' > temp2.txt
cat temp.txt | grep fileclose | awk 'NR % 2 == 0' | cut -d " " -f3 > hpc1.txt
diff temp.txt temp2.txt | grep fileclose | cut -d " " -f4 > hpc2.txt
rm temp.txt temp2.txt
