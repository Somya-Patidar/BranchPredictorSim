import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

BASE = Path(__file__).resolve().parent.parent
csv_file = BASE / "results/csv/benchmark.csv"
out_file = BASE / "results/plots/accuracy.png"

df = pd.read_csv(csv_file)

avg = df.groupby("Predictor")["Accuracy"].mean().sort_values(ascending=False)

plt.figure(figsize=(8,5))
plt.bar(avg.index, avg.values)
plt.ylabel("Average Accuracy (%)")
plt.title("BranchPredictorSim - Predictor Accuracy")
plt.xticks(rotation=20)
plt.tight_layout()
plt.savefig(out_file,dpi=300)
plt.close()

print(f"Saved {out_file}")