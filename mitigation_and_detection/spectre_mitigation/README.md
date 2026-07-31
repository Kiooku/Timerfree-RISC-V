# Spectre mitigation

This folder contains two mitigations against the Spectre attack for all the different timer-less methods:
- Fence insertion for speculation control;
- Masking-based index sanitization.


# Run

> [!NOTE]
> The compilation is the same for the two mitigations.

```
# Compile for thread counter
gcc -O1 -march=rv64gc -o spectre_timerfree_fence_mitigation spectre_timerfree_fence_mitigation.c -lpthread
taskset -c 0 ./spectre_timerfree_fence_mitigation

# Compile for clock fixed
gcc spectre_clock_monotonic_masking_based_index_mitigation.c -o spectre_clock_monotonic_masking_based_index_mitigation

# Compile for perf_event_open
gcc spectre_perf_event_open_fence_mitigation.c -o spectre_perf_event_open_fence_mitigation

# Compile with rdcycle
gcc spectre_rdcycle_masking_based_index_mitigation.c -Os -o spectre_rdcycle_masking_based_index_mitigation
```

# Tested on 
C910
