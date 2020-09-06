import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("distance_gen_data.txt")

data = data.groupby(['param'], as_index=False).mean()

plt.plot(data['param']*1000, data['distance']*1000)
plt.xlabel('parameter avg_diatange(m)')
plt.ylabel('true avg_distance(m)')
plt.title('avg_distance : parameter - true value')
plt.show()