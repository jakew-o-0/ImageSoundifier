import matplotlib.pyplot as plt
import numpy as np

wavtab = []
for i in range(0, 15):
    path = "./wave_tables/"
    path += str(i)
    data = np.fromfile(path, float)
    for i in data:
        wavtab.append(i)
    

plt.plot(wavtab)
plt.show()