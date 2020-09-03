import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# load data

columns = ['handoff']
data = pd.read_csv("data.txt", names=columns)
handoff = data['handoff'].values


# plot histogram of handoff

counts = np.bincount(handoff)

fig, ax = plt.subplots()
ax.bar(range(len(counts)), counts, width=1, align='center', edgecolor='black')
ax.set(xticks=range(len(counts)), xlim=[-1, len(counts)])

for i in range(len(counts)):
    plt.text(x=i, 
             y=counts[i] + max(counts)/100, 
             s=str(counts[i]), 
             horizontalalignment='center')

plt.title('histogram of handoff')
plt.show()