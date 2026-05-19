gcc -O1 -march=rv64gc -o flush_reload_timerfree flush_reload_timerfree.c -lpthread
taskset -c 0 ./flush_reload_timerfree
gcc flush_reload_clock_fixed.c -o flush_reload_clock_fixed
gcc flush_reload_rdcycle.c -Os -o flush_reload_rdcycle
