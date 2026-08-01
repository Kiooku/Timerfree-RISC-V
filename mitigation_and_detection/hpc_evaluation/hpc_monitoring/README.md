# HPC Monitoring

Event monitored:
- L1 ICache Access Counter: `hpmcounter3`
- L1 ICache Miss Counter: `hpmcounter4`
- Conditional Branch Mispredict Counter: `hpmcounter8`
- Indirect Branch Mispredict Counter: `hpmcounter10`
- Indirect Branch Instruction Counter: `hpmcounter11`
- L1 DCache Read Access Counter: `hpmcounter14`
- L1 DCache Read Miss Counter: `hpmcounter15`
- L1 DCache Write Access Counter: `hpmcounter16`
- L1 DCache Write Miss Counter: `hpmcounter17`

# Run

1. Modify all the scripts (e.g., `nano *.c`) to use the counters you want to use;
2. Go to the dedicated folder to store HPC values (e.g., `Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/flush_fault/cispa_ff_hpc/`);
3. Use the `create_benchmark_detection.sh` script *(The time differs between the scripts. It can be longer than 30 mins)*:
```bash
# Flush+Fault: Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/flush_fault/cispa_ff_hpc/
../../create_benchmark_detection.sh 50 ../flush_fault_clock_fixed_hpc ../../run_multiple_time.sh flush_fault_clock_fixed_hpc
../../create_benchmark_detection.sh 50 ../flush_fault_clock_fixed_process_id_hpc ../../run_multiple_time.sh flush_fault_clock_fixed_process_id_hpc
../../create_benchmark_detection.sh 50 ../flush_fault_clock_fixed_thread_id_hpc ../../run_multiple_time.sh flush_fault_clock_fixed_thread_id_hpc
../../create_benchmark_detection.sh 50 ../flush-fault-hpc ../../run_multiple_time.sh flush_fault_hpc
../../create_benchmark_detection.sh 50 ../flush_fault_perf_event_open_hpc ../../run_multiple_time.sh flush_fault_perf_event_open_hpc

# Flush+Ret: Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/flush_ret/cispa_fr_hpc/
../../create_benchmark_detection.sh 50 ../flush_ret_clock_fixed_hpc ../../run_multiple_time.sh flush_ret_clock_fixed_hpc
../../create_benchmark_detection.sh 50 ../flush_ret_clock_fixed_process_id_hpc ../../run_multiple_time.sh flush_ret_clock_fixed_process_id_hpc
../../create_benchmark_detection.sh 50 ../flush_ret_clock_fixed_thread_id_hpc ../../run_multiple_time.sh flush_ret_clock_fixed_thread_id_hpc
../../create_benchmark_detection.sh 50 ../flush_ret_hpc ../../run_multiple_time.sh flush_ret_hpc
../../create_benchmark_detection.sh 50 ../flush_ret_perf_event_open_hpc ../../run_multiple_time.sh flush_ret_perf_event_open_hpc

# Flush+Reload: Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/flush_reload/fr_hpc/
../../create_benchmark_detection.sh 50 ../flush_reload_clock_fixed_hpc ../../run_multiple_time.sh fr_clock_fixed_hpc
../../create_benchmark_detection.sh 50 ../flush_reload_rdcycle_hpc ../../run_multiple_time.sh fr_rdcycle_hpc
../../create_benchmark_detection.sh 50 ../flush_reload_perf_event_open_hpc ../../run_multiple_time.sh fr_perf_event_open_hpc

# Flush+Flush: Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/flush_flush/ff_hpc/
../../create_benchmark_detection.sh 50 ../flush_flush_clock_fixed_hpc ../../run_multiple_time.sh ff_clock_fixed_hpc
../../create_benchmark_detection.sh 50 ../flush_flush_rdcycle_hpc ../../run_multiple_time.sh ff_rdcycle_hpc

# Spectre: Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/spectre/spectre_hpc/
../../create_benchmark_detection.sh 50 ../spectre_clock_monotonic_hpc ../../run_multiple_time.sh spectre_clock_monotonic_hpc
../../create_benchmark_detection.sh 50 ../spectre_clock_process_hpc ../../run_multiple_time.sh spectre_clock_process_hpc
../../create_benchmark_detection.sh 50 ../spectre_clock_thread_hpc ../../run_multiple_time.sh spectre_clock_thread_hpc
../../create_benchmark_detection.sh 50 ../spectre_rdcycle_hpc ../../run_multiple_time.sh spectre_rdcycle_hpc
../../create_benchmark_detection.sh 50 ../spectre_perf_event_open_hpc ../../run_multiple_time.sh spectre_perf_event_open_hpc

# Begnign apps: Timerfree-RISC-V/mitigation_and_detection/hpc_evaluation/hpc_monitoring/rv8/rv8_hpc/
../../create_benchmark_detection.sh 50 ../aes_hpc ../../run_multiple_time.sh aes_hpc
../../create_benchmark_detection.sh 50 ../bigint_hpc ../../run_multiple_time.sh bigint_hpc
../../create_benchmark_detection.sh 50 ../miniz_hpc ../../run_multiple_time.sh miniz_hpc
../../create_benchmark_detection.sh 50 ../qsort_hpc ../../run_multiple_time.sh qsort_hpc
```

# Tested on
C910
