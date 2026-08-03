# Visualization of HPC values

> [!NOTE]
> For different background noises the value of hpc recorded can vary.
> In paper we average out the value in the least noise scenario.
> But because of limited time we could not record all the values. Scripts can be used to re run this experiment.
> All scripts are verified and correct to rerun these HPC experiments on RISC-V cores

Example of a plot (red: malicious/ blue: benign):

![HPC plot for L1 ICache Miss Counter](https://github.com/Kiooku/Timerfree-RISC-V/blob/main/mitigation_and_detection/hpc_evaluation/visualization/plots/Ratio_L1_DCache_Read_Counter.png)

# Run
```bash
python3 visualize_mutiple_bar_chart.py
```
