import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("distance_gen_data.txt")

data = data.groupby(['param'], as_index=False).mean()

plt.figure(1)
plt.plot(data['param']*1000, data['distance']*1000, label='real value')
plt.plot(data['param']*1000, data['param']*1000, label='expected value')
plt.xlabel('expected avg_diatange(m)')
plt.ylabel('real avg_distance(m)')
plt.title('avg_distance : expected - real')
plt.legend()

plt.figure(2)
plt.plot(data['param']*1000, data['distance']*1000)
plt.xlabel('expected avg_diatange(m)')
plt.ylabel('real avg_distance(m)')
plt.title('avg_distance : real value')
plt.show()