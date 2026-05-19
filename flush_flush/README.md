gcc -O1 -march=rv64gc -o flush_flush_timerfree flush_flush_timerfree.c -lpthread
taskset -c 0 ./flush_flush_timerfree
gcc flush_flush_clock_fixed.c -o flush_flush_clock_fixed
gcc flush_flush_rdcycle.c -Os -o flush_flush_rdcycle
