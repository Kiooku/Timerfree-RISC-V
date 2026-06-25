# Timerfree-RISC-V

Repository of the paper "Timerfree cache timing attacks on RISC-V".

## Materials

You'll find in each folder a README file describing how to run it.

The timerfree methods used are:
- **`rdcycle`**: This RISC-V instruction provides a high-resolution baseline for evaluating alternative timing sources.
- **Counter Thread**: A POSIX thread pinned to a sibling hart continuously increments a shared sw counter. This follows the counter-thread idea used in ARMageddon. It is sensitive to scheduling, interrupts, and harts.
- **clock gettime**: We tested POSIX clock gettime with two clock IDs: clock process cputime id and clock monotonic raw. Its effective resolution depends on the kernel, clock source, syscall path, and scheduling.
- **perf event open**: Linux syscall (perf event open) exposes hardware cycle events. We configure it to count CPU cycles for the monitored task while excluding kernel and hypervisor time. This method depends on kernel configuration and the perf event paranoid policy, which controls whether unprivileged users can access performance counter.

You'll find all the atacks explained in the paper:
- `AES_cache_attack`: `Flush+Reload` attack on AES using T-Table of openssl-1.1.0f *(Inspired by [`nepoche` `Flush+Reload` github repository](https://github.com/nepoche/Flush-Reload))*;
- `flush_fault`: `Flush+Fault` and `Flush+Ret` from the ["A Security RISC: Microarchitectural Attacks on Hardware RISC-V CPUs"](https://misc0110.net/files/riscv_attacks_sp23.pdf) paper implemented with timerfree methods;
- `flush_flush`: `Flush+Flush` implemented using timerfree methods;
- `flush_reload`: `Flush+Reload` implemented using timerfree methods;
- `main_page_walk`: Distinction between "Page walk" and "No page walk" using `perf_event_open`;
- `spectre`: Spectre attack of the paper ["Spectre Attacks: Exploiting Speculative Execution"](https://spectreattack.com/spectre.pdf) with timerfree methods;
- `CoverChannel`: Covert channel from the paper ["Cross-Core Covert Channel for RISC-V: Implementation, Countermeasures and Cross-Platform Analysis"](https://telecom-paris.hal.science/hal-05510026/) with timerfree methods.

## CPU Usage Impact with our Attacks

| CPU Usage | Background Applications / Stress Linux Test                    |
| --------- | -------------------------------------------------------------- |
| 25%       | One RV8 process (*`AES`*)                                      |
| 50%       | Two RV8 processes (*`AES`*, *`bigint`*)                        |
| 75%       | Three RV8 processes (*`AES`*, *`bigint`*, *`miniz`*)           |
| 100%      | Four RV8 processes (*`AES`*, *`bigint`*, *`miniz`*, *`qsort`*) |

## Citing Paper and Artifacts

If you use our results in your research, please cite our paper as:
```
TODO
```

And our artifacts as:
```
TODO
```
