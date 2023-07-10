import matplotlib.pyplot as plt
import numpy as np

wavtab = []
for i in range(0, 15):
    path = "./wave_tables/"
    path += str(i)
    with open(path, "rb") as wavetable:
        buff = bytearray(wavetable.read(wavetable.__sizeof__()))
        data = np.frombuffer(buff, dtype=np.float32);
        print(data)
        wavtab.append(data)
    
for i in wavtab:
    print(i)

plt.plot(wavtab)
plt.show()