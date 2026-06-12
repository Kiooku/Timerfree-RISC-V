# Retired instructions for Page Table from the [Security-RISC repository](https://github.com/cispa/Security-RISC/tree/main) with timerless methods

This experiment shows that a page table walk does not issue additional instructions that could be observed using the thread counter or `clock_fixed`.

However, we have seen a differences between a "Page walk" and a "Page no walk" using `perf_event_open`.

# Run
Run `make` followed by `./main` or `./main_clock_fixed` or `./main_perf_event_open` or `./main_thread`.

# Works on 
C910
