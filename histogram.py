import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


# load data
data = pd.read_csv("data.txt")

# plot histogram

fig = plt.figure(1)
ax = fig.subplots()

counts = np.bincount(data['handoff'])

ax.bar(range(len(counts)), counts, width=1, align='center', edgecolor='black')
ax.set(xticks=range(len(counts)), xlim=[-1, len(counts)])

for i in range(len(counts)):
    plt.text(x=i,
             y=counts[i] + max(counts)/100,
             s=str(counts[i]),
             horizontalalignment='center')

plt.title('histogram of handoff : %d' % (len(data['handoff'])))

plt.show()
