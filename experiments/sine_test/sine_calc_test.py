import matplotlib.pyplot as plt
import numpy as np

sin_wav = []
key = 110 * pow(2, (1/12) * 0)
for i in range(0, int(44100 / 110)):
    sin_wav.append(0.5 * np.sin(2 * np.pi * key * (i / 44100)))
    
sin_wav1 = []
key = 110 * pow(2, (1/12) * 10)
for i in range(0, int(44100/key)):
    sin_wav1.append( 0.5 * np.sin(2 * np.pi * key * i / 44100))

for i in range(0, 256):
    sin_wav.append(0)

for i in range(0, int(44100 / key)):
    sin_wav.append(sin_wav1[i])

plt.plot(sin_wav)

plt.show()
