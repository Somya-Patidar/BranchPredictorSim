from pathlib import Path
import subprocess
import pandas as pd

BASE = Path(__file__).resolve().parent.parent
csv_file = BASE / "results/csv/benchmark.csv"

if not csv_file.exists():
    raise FileNotFoundError(
        "Run './BranchPredictorSim --benchmark' first."
    )

scripts = [
    "plot_accuracy.py",
    "plot_mpki.py",
    "plot_ipc.py",
]

for script in scripts:
    subprocess.run(
        ["python3", str(BASE/"scripts"/script)],
        check=True
    )

df = pd.read_csv(csv_file)

summary = []

summary.append("BranchPredictorSim Benchmark Summary\n")
summary.append("="*40 + "\n\n")

summary.append(
    f"Total Benchmark Runs: {len(df)}\n"
)

summary.append(
    f"Unique Workloads: {df['Trace'].nunique()}\n"
)

summary.append(
    f"Predictors Evaluated: {df['Predictor'].nunique()}\n\n"
)

summary.append("Average Results\n")
summary.append("-"*25 + "\n")

avg = df.groupby("Predictor")[["Accuracy","MPKI","IPC"]].mean()

for predictor,row in avg.iterrows():

    summary.append(
        f"{predictor}\n"
        f"  Accuracy: {row['Accuracy']:.2f}%\n"
        f"  MPKI:     {row['MPKI']:.2f}\n"
        f"  IPC:      {row['IPC']:.3f}\n\n"
    )

out = BASE/"results/plots/summary.txt"

out.write_text("".join(summary))

print(f"Saved {out}")