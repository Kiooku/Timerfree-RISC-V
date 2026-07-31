import pandas as pd
import matplotlib.pyplot as plt


"""
path_hpc_files: list[str] = ["hpc_results/ff_hpc/L1I/ff_clock_fixed_hpc", 
                             "hpc_results/ff_hpc/L1I/ff_rdcycle_hpc", 

                             "hpc_results/fr_hpc/L1I/fr_clock_fixed_hpc", 
                             "hpc_results/fr_hpc/L1I/fr_rdcycle_hpc", 
                             "hpc_results/fr_hpc/L1I/fr_perf_event_open_hpc",

                             "hpc_results/cispa_ff_hpc/L1I/flush_fault_clock_fixed_hpc", 
                             "hpc_results/cispa_ff_hpc/L1I/flush_fault_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_ff_hpc/L1I/flush_fault_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_ff_hpc/L1I/flush_fault_hpc", 
                             "hpc_results/cispa_ff_hpc/L1I/flush_fault_perf_event_open_hpc",
                             
                             "hpc_results/cispa_fr_hpc/L1I/flush_ret_clock_fixed_hpc", 
                             "hpc_results/cispa_fr_hpc/L1I/flush_ret_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_fr_hpc/L1I/flush_ret_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_fr_hpc/L1I/flush_ret_hpc", 
                             "hpc_results/cispa_fr_hpc/L1I/flush_ret_perf_event_open_hpc",

                             "hpc_results/spectre_hpc/L1I/spectre_clock_monotonic_hpc", 
                             "hpc_results/spectre_hpc/L1I/spectre_clock_process_hpc", 
                             "hpc_results/spectre_hpc/L1I/spectre_clock_thread_hpc", 
                             "hpc_results/spectre_hpc/L1I/spectre_rdcycle_hpc", 
                             "hpc_results/spectre_hpc/L1I/spectre_perf_event_open_hpc",

                             "hpc_results/rv8_hpc/L1I/aes_hpc", 
                             "hpc_results/rv8_hpc/L1I/bigint_hpc",
                             "hpc_results/rv8_hpc/L1I/miniz_hpc",
                             "hpc_results/rv8_hpc/L1I/qsort_hpc"]
"""
"""
path_hpc_files: list[str] = ["hpc_results/ff_hpc/L1D_Read/ff_clock_fixed_hpc", 
                             "hpc_results/ff_hpc/L1D_Read/ff_rdcycle_hpc", 

                             "hpc_results/fr_hpc/L1D_Read/fr_clock_fixed_hpc", 
                             "hpc_results/fr_hpc/L1D_Read/fr_rdcycle_hpc", 
                             "hpc_results/fr_hpc/L1D_Read/fr_perf_event_open_hpc",

                             "hpc_results/cispa_ff_hpc/L1D_Read/flush_fault_clock_fixed_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Read/flush_fault_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Read/flush_fault_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Read/flush_fault_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Read/flush_fault_perf_event_open_hpc",
                            
                             "hpc_results/cispa_fr_hpc/L1D_Read/flush_ret_clock_fixed_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Read/flush_ret_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Read/flush_ret_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Read/flush_ret_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Read/flush_ret_perf_event_open_hpc",

                             "hpc_results/spectre_hpc/L1D_Read/spectre_clock_monotonic_hpc", 
                             "hpc_results/spectre_hpc/L1D_Read/spectre_clock_process_hpc", 
                             "hpc_results/spectre_hpc/L1D_Read/spectre_clock_thread_hpc", 
                             "hpc_results/spectre_hpc/L1D_Read/spectre_rdcycle_hpc", 
                             "hpc_results/spectre_hpc/L1D_Read/spectre_perf_event_open_hpc",

                             "hpc_results/rv8_hpc/L1D_Read/aes_hpc", 
                             "hpc_results/rv8_hpc/L1D_Read/bigint_hpc",
                             "hpc_results/rv8_hpc/L1D_Read/miniz_hpc",
                             "hpc_results/rv8_hpc/L1D_Read/qsort_hpc"]

"""
"""
path_hpc_files: list[str] = ["hpc_results/ff_hpc/L1D_Write/ff_clock_fixed_hpc", 
                             "hpc_results/ff_hpc/L1D_Write/ff_rdcycle_hpc", 

                             "hpc_results/fr_hpc/L1D_Write/fr_clock_fixed_hpc", 
                             "hpc_results/fr_hpc/L1D_Write/fr_rdcycle_hpc", 
                             "hpc_results/fr_hpc/L1D_Write/fr_perf_event_open_hpc",

                             "hpc_results/cispa_ff_hpc/L1D_Write/flush_fault_clock_fixed_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Write/flush_fault_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Write/flush_fault_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Write/flush_fault_hpc", 
                             "hpc_results/cispa_ff_hpc/L1D_Write/flush_fault_perf_event_open_hpc",
                            
                             "hpc_results/cispa_fr_hpc/L1D_Write/flush_ret_clock_fixed_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Write/flush_ret_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Write/flush_ret_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Write/flush_ret_hpc", 
                             "hpc_results/cispa_fr_hpc/L1D_Write/flush_ret_perf_event_open_hpc",

                             "hpc_results/spectre_hpc/L1D_Write/spectre_clock_monotonic_hpc", 
                             "hpc_results/spectre_hpc/L1D_Write/spectre_clock_process_hpc", 
                             "hpc_results/spectre_hpc/L1D_Write/spectre_clock_thread_hpc", 
                             "hpc_results/spectre_hpc/L1D_Write/spectre_rdcycle_hpc", 
                             "hpc_results/spectre_hpc/L1D_Write/spectre_perf_event_open_hpc",

                             "hpc_results/rv8_hpc/L1D_Write/aes_hpc", 
                             "hpc_results/rv8_hpc/L1D_Write/bigint_hpc",
                             "hpc_results/rv8_hpc/L1D_Write/miniz_hpc",
                             "hpc_results/rv8_hpc/L1D_Write/qsort_hpc"]
"""
"""
path_hpc_files: list[str] = ["hpc_results/ff_hpc/BranchMispredict/ff_clock_fixed_hpc", 
                             "hpc_results/ff_hpc/BranchMispredict/ff_rdcycle_hpc", 

                             "hpc_results/fr_hpc/BranchMispredict/fr_clock_fixed_hpc", 
                             "hpc_results/fr_hpc/BranchMispredict/fr_rdcycle_hpc", 
                             "hpc_results/fr_hpc/BranchMispredict/fr_perf_event_open_hpc",

                             "hpc_results/cispa_ff_hpc/BranchMispredict/flush_fault_clock_fixed_hpc", 
                             "hpc_results/cispa_ff_hpc/BranchMispredict/flush_fault_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_ff_hpc/BranchMispredict/flush_fault_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_ff_hpc/BranchMispredict/flush_fault_hpc", 
                             "hpc_results/cispa_ff_hpc/BranchMispredict/flush_fault_perf_event_open_hpc",
                            
                             "hpc_results/cispa_fr_hpc/BranchMispredict/flush_ret_clock_fixed_hpc", 
                             "hpc_results/cispa_fr_hpc/BranchMispredict/flush_ret_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_fr_hpc/BranchMispredict/flush_ret_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_fr_hpc/BranchMispredict/flush_ret_hpc", 
                             "hpc_results/cispa_fr_hpc/BranchMispredict/flush_ret_perf_event_open_hpc",

                             "hpc_results/spectre_hpc/BranchMispredict/spectre_clock_monotonic_hpc", 
                             "hpc_results/spectre_hpc/BranchMispredict/spectre_clock_process_hpc", 
                             "hpc_results/spectre_hpc/BranchMispredict/spectre_clock_thread_hpc", 
                             "hpc_results/spectre_hpc/BranchMispredict/spectre_rdcycle_hpc", 
                             "hpc_results/spectre_hpc/BranchMispredict/spectre_perf_event_open_hpc",

                             "hpc_results/rv8_hpc/BranchMispredict/aes_hpc", 
                             "hpc_results/rv8_hpc/BranchMispredict/bigint_hpc",
                             "hpc_results/rv8_hpc/BranchMispredict/miniz_hpc",
                             "hpc_results/rv8_hpc/BranchMispredict/qsort_hpc"]
"""
path_hpc_files: list[str] = ["hpc_results/ff_hpc/IndirectBranch/ff_clock_fixed_hpc", 
                             "hpc_results/ff_hpc/IndirectBranch/ff_rdcycle_hpc", 

                             "hpc_results/fr_hpc/IndirectBranch/fr_clock_fixed_hpc", 
                             "hpc_results/fr_hpc/IndirectBranch/fr_rdcycle_hpc", 
                             "hpc_results/fr_hpc/IndirectBranch/fr_perf_event_open_hpc",

                             "hpc_results/cispa_ff_hpc/IndirectBranch/flush_fault_clock_fixed_hpc", 
                             "hpc_results/cispa_ff_hpc/IndirectBranch/flush_fault_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_ff_hpc/IndirectBranch/flush_fault_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_ff_hpc/IndirectBranch/flush_fault_hpc", 
                             "hpc_results/cispa_ff_hpc/IndirectBranch/flush_fault_perf_event_open_hpc",
                            
                             "hpc_results/cispa_fr_hpc/IndirectBranch/flush_ret_clock_fixed_hpc", 
                             "hpc_results/cispa_fr_hpc/IndirectBranch/flush_ret_clock_fixed_process_id_hpc", 
                             "hpc_results/cispa_fr_hpc/IndirectBranch/flush_ret_clock_fixed_thread_id_hpc", 
                             "hpc_results/cispa_fr_hpc/IndirectBranch/flush_ret_hpc", 
                             "hpc_results/cispa_fr_hpc/IndirectBranch/flush_ret_perf_event_open_hpc",

                             "hpc_results/spectre_hpc/IndirectBranch/spectre_clock_monotonic_hpc", 
                             "hpc_results/spectre_hpc/IndirectBranch/spectre_clock_process_hpc", 
                             "hpc_results/spectre_hpc/IndirectBranch/spectre_clock_thread_hpc", 
                             "hpc_results/spectre_hpc/IndirectBranch/spectre_rdcycle_hpc", 
                             "hpc_results/spectre_hpc/IndirectBranch/spectre_perf_event_open_hpc",

                             "hpc_results/rv8_hpc/IndirectBranch/aes_hpc", 
                             "hpc_results/rv8_hpc/IndirectBranch/bigint_hpc",
                             "hpc_results/rv8_hpc/IndirectBranch/miniz_hpc",
                             "hpc_results/rv8_hpc/IndirectBranch/qsort_hpc"]


names: list[str] = []
#ratios: list[float] = []
"""
results: dict = {
    "L1 ICache Access Counter": [],
    "L1 ICache Miss Counter": [],
    "Ratio L1 ICache Counter": []
}
"""
"""
results: dict = {
    "L1 DCache Read Access Counter": [],
    "L1 DCache Read Miss Counter": [],
    "Ratio L1 DCache Read Counter": []
}
"""
"""
results: dict = {
    "L1 DCache Write Access Counter": [],
    "L1 DCache Write Miss Counter": [],
    "Ratio L1 DCache Write Counter": []
}
"""
"""
results: dict = {
    "Conditional Branch Mispredict Counter": [],
    "Indirect Branch Mispredict Counter": [],
}
"""
results: dict = {
    "Indirect Branch Mispredict Counter": [],
    "Indirect Branch Instruction Counter": [],
    "Ratio Indirect Branch Counter": []
}


for path in path_hpc_files:
    current_path: str = path + "/hpc1.txt"
    data_access  = pd.read_csv(current_path, header=None)
    data_access = pd.DataFrame(data_access)

    min_access = data_access[0].min()
    max_access = data_access[0].max()
    median_access = data_access[0].median()
    mean_access = data_access[0].mean(numeric_only=True)
    print(f"Min (Attacker access): \t\t{min_access}") 
    print(f"Max (Attacker access): \t\t{max_access}")
    print(f"Median (Attacker access): \t{median_access}")
    print(f"Mean (Attacker access): \t\t{mean_access}")

    current_path = path + "/hpc2.txt"
    data_miss = pd.read_csv(current_path, header=None)
    data_miss = pd.DataFrame(data_miss)
    min_miss = data_miss[0].min()
    max_miss = data_miss[0].max()
    median_miss = data_miss[0].median()
    mean_miss = data_miss[0].mean(numeric_only=True)
    print(f"Min (Attacker access): \t\t{min_miss}") 
    print(f"Max (Attacker access): \t\t{max_miss}")
    print(f"Median (Attacker access): \t{median_miss}")
    print(f"Mean (Attacker access): \t\t{mean_miss}")

    ratio = mean_miss / mean_access

    print(f"Ratio (Miss/Hit) [{path.split("/")[-1]}] = {ratio}")

    names.append(path.split("/")[-1])
    #ratios.append(ratio)
    
    """
    results["L1 ICache Access Counter"].append(mean_access)
    results["L1 ICache Miss Counter"].append(mean_miss)
    results["Ratio L1 ICache Counter"].append(ratio)
    """
    """
    results["L1 DCache Read Access Counter"].append(mean_access)
    results["L1 DCache Read Miss Counter"].append(mean_miss)
    results["Ratio L1 DCache Read Counter"].append(ratio)
    """
    """
    results["L1 DCache Write Access Counter"].append(mean_access)
    results["L1 DCache Write Miss Counter"].append(mean_miss)
    results["Ratio L1 DCache Write Counter"].append(ratio)
    """
    """
    results["Indirect Branch Mispredict Counter"].append(mean_access)
    results["Conditional Branch Mispredict Counter"].append(mean_miss)
    """
    results["Indirect Branch Mispredict Counter"].append(mean_access)
    results["Indirect Branch Instruction Counter"].append(mean_miss)
    results["Ratio Indirect Branch Counter"].append(ratio)


## Bar chart

#fig, ax = plt.subplots()
#ax.bar(names, ratios)

bar_colors = ["tab:red", "tab:red", "tab:red", "tab:red", "tab:red", 
              "tab:red", "tab:red", "tab:red", "tab:red", "tab:red", 
              "tab:red", "tab:red", "tab:red", "tab:red", "tab:red", 
              "tab:red", "tab:red", "tab:red", "tab:red", "tab:red", 
              "tab:blue", "tab:blue", "tab:blue", "tab:blue"]
print(len(bar_colors), len(path_hpc_files))

for k in results.keys():
    print(results[k])
    fig, ax = plt.subplots()
    ax.bar(names, results[k], color=bar_colors)
    plt.xticks(range(len(names)), names, rotation=90)
    ax.set_ylabel("Number of instruction")
    ax.set_title(k)
    plt.tight_layout()

    plt.savefig(f"plots/{k.replace(" ", "_")}")

    plt.show()
"""
fig, ax = plt.subplots(layout='constrained')

res = ax.grouped_bar(results, tick_label=names, group_spacing=1)
for container in res.bar_containers:
    ax.bar_label(container, padding=3)

ax.set_ylabel("Number of instruction")
ax.set_title("HPC study per process")
ax.legend(loc="upper left", ncols=3)

plt.show()
"""