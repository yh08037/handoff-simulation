import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# load data

data_r = pd.read_csv("data_r.txt")
data_s = pd.read_csv("data_s.txt")
data_d = pd.read_csv("data_d.txt")
data_t = pd.read_csv("data_t.txt")


plt.subplot(2, 2, 1)
plt.plot(data_r['size_cell']*1000, data_r['handoff'])
plt.xlabel('size_cell(m)')
plt.ylabel('handoff')
plt.title('size_cell - avg_handoff')

plt.subplot(2, 2, 2)
plt.plot(data_s['avg_speed'], data_s['handoff'])
plt.xlabel('avg_speed(km/h)')
plt.ylabel('handoff')
plt.title('avg_speed - avg_handoff')

plt.subplot(2, 2, 3)
plt.plot(data_d['avg_distance']*1000, data_d['handoff'])
plt.xlabel('avg_distance(m)')
plt.ylabel('handoff')
plt.title('avg_distance - avg_handoff')

plt.subplot(2, 2, 4)
plt.plot(data_t['avg_duration']*60, data_t['handoff'])
plt.xlabel('avg_duration(min)')
plt.ylabel('handoff')
plt.title('avg_duration - avg_handoff')


plt.tight_layout()
plt.show()