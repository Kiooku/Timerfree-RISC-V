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


| **Attack**       | **CPU usage** | **`rdcycle`** | **`perf_event_open`**       | **Counter thread** | **`clock_gettime`** |
|-----------------------|--------------------|-------------------------|-------------------------------------------|-------------------------|----------------------------------|
| Spectre V1            | 25\%               | 50/50                   | 50/50                                     | 26/50                   | 50/50                            |
| Spectre V1            | 50\%               | 50/50                   | 50/50                                     | 34/50                   | 49/50                            |
| Spectre V1            | 75\%               | 50/50                   | 49/50                                     | 34/50                   | 49/50                            |
| Spectre V1            | 100\%              | 50/50                   | 45/50                                     | 21/50                   | 50/50                            |
| AES cache             | 25\%               | 48/50                   | 35/50                                     | 50/50                   | 50/50                            |
| AES cache             | 50\%               | 49/50                   | 38/50                                     | 50/50                   | 50/50                            |
| AES cache             | 75\%               | 49/50                   | 31/50                                     | 48/50                   | 50/50                            |
| AES cache             | 100\%              | 48/50                   | 40/50                                     | 38/50                   | 50/50                            |
| Covert Channel        | 25\%               | 100\%                   | -                                         | 99\%                    | -                                |
| Covert Channel        | 50\%               | 100\%                   | -                                         | 99\%                    | -                                |
| Covert Channel        | 75\%               | 100\%                   | -                                         | 99\%                    | -                                |
| Covert Channel        | 100\%              | 100\%                   | -                                         | 99\%                    | -                                |
| `Flush+Reload` | 25\%               | 50/50                   | 38/40                                     | 50/50                   | 49/50                            |
| `Flush+Reload` | 50\%               | 50/50                   | 37/50                                     | 50/50                   | 50/50                            |
| `Flush+Reload` | 75\%               | 50/50                   | 40/50                                     | 20/50                   | 49/50                            |
| `Flush+Reload` | 100\%              | 50/50                   | 38/50                                     | 10/20                   | 50/50                            |
| `Flush+Flush`  | 25\%               | 50/50                   | -                                         | 50/50                   | 50/50                            |
| `Flush+Flush`  | 50\%               | 50/50                   | -                                         | 50/50                   | 50/50                            |
| `Flush+Flush`  | 75\%               | 48/50                   | -                                         | 50/50                   | 50/50                            |
| `Flush+Flush`  | 100\%              | 49/50                   | -                                         | 50/50                   | 50/50                            |
| `Flush+Fault`  | 25\%               | 100\%                   | 100\%                                     | 100\%                   | 100\%                            |
| `Flush+Fault`  | 50\%               | 100\%                   | 100\%                                     | 100\%                   | 100\%                            |
| `Flush+Fault`  | 75\%               | 100\%                   | 100\%                                     | 100\%                   | 50\%                             |
| `Flush+Fault`  | 100\%              | 100\%                   | 100\%                                     | 50\%                    | 50\%                             |
| `Flush+Ret`    | 25\%               | 100\%                   | 100\%                                     | 100\%                   | -                                |
| `Flush+Ret`    | 50\%               | 100\%                   | 100\%                                     | 100\%                   | -                                |
| `Flush+Ret`    | 75\%               | 100\%                   | 100\%                                     | 100\%                   | -                                |
| `Flush+Ret`    | 100\%              | 100\%                   | 100\%                                     | 50\%                    | -                                |


## Citing Paper and Artifacts

If you use our results in your research, please cite our paper as:
```
TODO
```

And our artifacts as:
```
TODO
```
