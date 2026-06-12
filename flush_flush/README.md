# Flush+Flush

`Flush+Flush` attack on a toy example using timerfree methods.

The attacker distinguish the action of the victim (`vote_a` or `vote_b`) using the `Flush+Flush` attack.

This example is inpired by the exercice 2 of [Computer Architecture and System Software - Session 7: Caches and Microarchitectural Timing Attacks](https://cass-kul.github.io/exercises/7-cache/) from KU Louvain.

# Run

```
# Compile for thread counter
gcc -O1 -march=rv64gc -o flush_flush_timerfree flush_flush_timerfree.c -lpthread
taskset -c 0 ./flush_flush_timerfree

# Compile for clock fixed
gcc flush_flush_clock_fixed.c -o flush_flush_clock_fixed

# Compile for perf_event_open
gcc flush_flush_perf_event_open.c -o flush_flush_perf_event_open

# Compile for rdcycle
gcc flush_flush_rdcycle.c -Os -o flush_flush_rdcycle
```

# Tested on
C910
