import matplotlib.pyplot as plt
import pandas as pd
import sys

def main():
    if len(sys.argv) != 2:
        print(f"USAGE: {sys.argv[0]} <flush-fault.csv|fault-ret.csv>")
        exit(0)
    fname = sys.argv[1]
    
    print(fname)
    df = pd.read_csv(fname)
    print(df)
    df.plot(x="x axis", y="y axis")
