# Timerfree-RISC-V

Repository of the paper "Timerfree cache timing attacks on RISC-V".

## Materials

You'll find in each folder a README file describing how to run it.

The timerfree methods used are:
- thread: TODO explain using Mahreen description;
- `perf_event_open`: TODO explain using Mahreen description;
- clock_fixed: TODO explain using Mahreen description.

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


| Attack | CPU Usage | `rdcycle` | Perf Counter | Thread Clock | Clock Fixed |
|---------|-----------|-----------|--------------|--------------|-------------|
| Spectre V1 | 25% | XXX | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| Spectre V1 | 50% | XXX | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| Spectre V1 | 75% | XXX | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| Spectre V1 | 100% | XXX | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| AES Cache | 25% | XXX | $\color{orange}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| AES Cache | 50% | XXX | $\color{orange}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| AES Cache | 75% | XXX | $\color{red}{\textsf{Success}}$ | $\color{orange}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| AES Cache | 100% | XXX | $\color{red}{\textsf{Success}}$ | $\color{orange}{\textsf{Success}}$ | $\color{green}{\textsf{Success}}$ |
| Page Walk | 25% | - | $\color{green}{\textsf{Success}}$ | - | - |
| Page Walk | 50% | - | $\color{green}{\textsf{Success}}$ | - | - |
| Page Walk | 75% | - | $\color{green}{\textsf{Success}}$ | - | - |
| Page Walk | 100% | - | $\color{green}{\textsf{Success}}$ | - | - |
| Covert Channel | 25% | XXX | XXX | XXX | XXX |
| Covert Channel | 50% | XXX | XXX | XXX | XXX |
| Covert Channel | 75% | XXX | XXX | XXX | XXX |
| Covert Channel | 100% | XXX | XXX | XXX | XXX |

- $\color{green}{\textsf{Success}}$: Works 100% of the time
- $\color{orange}{\textsf{Success}}$: Works 90% of the time
- $\color{red}{\textsf{Success}}$: Works 35–40% of the time

## Citing Paper and Artifacts

If you use our results in your research, please cite our paper as:
```
TODO
```

And our artifacts as:
```
TODO
```
