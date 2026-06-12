# Flush+Reload

`Flush+Reload` attack on a toy example using timerfree methods.

The attacker distinguish the action of the victim (`vote_a` or `vote_b`) using the `Flush+Reload` attack.

This example is inpired by the exercice 2 of [Computer Architecture and System Software - Session 7: Caches and Microarchitectural Timing Attacks](https://cass-kul.github.io/exercises/7-cache/) from KU Louvain.

## Run
```
# Compile for thread counter
gcc -O1 -march=rv64gc -o flush_reload_timerfree flush_reload_timerfree.c -lpthread
taskset -c 0 ./flush_reload_timerfree

# Compile for clock fixed
gcc flush_reload_clock_fixed.c -o flush_reload_clock_fixed

# Compile for perf_event_open
gcc flush_reload_perf_event_open.c -o flush_reload_perf_event_open

# Compile with rdcycle
gcc flush_reload_rdcycle.c -Os -o flush_reload_rdcycle
```

## Tested on 
C910
