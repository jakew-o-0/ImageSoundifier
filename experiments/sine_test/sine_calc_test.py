import matplotlib.pyplot as plt
import numpy as np

PI = np.pi


def create_freq(x) -> float:
    A = 110
    k = x
    r = pow(2, (1/12) * k)
    return A*r


def create_sin(F, A, p):
    sin_wav = []
    s_rate = 44100

    for x in range(0, 256):
        point = A * np.sin(((2 * PI) * F * (x / s_rate)) + p)
        sin_wav.append(point)

    return sin_wav


F = create_freq(2)
sin_wav = create_sin(F, 0.5, 0)
F = create_freq(2)
sin_wav2 = create_sin(F, 0.2, 0.4)
F = create_freq(9)
sin_wav4 = create_sin(F, 0.8, 0.5)

sin_wav3 = []
for i in range(0, len(sin_wav) - 1):
    sin_wav3.append(sin_wav[i] + sin_wav2[i])

#for i in range(0, 256):
#    sin_wav3[i] += sin_wav4[i]

plt.plot(sin_wav)
#plt.plot(sin_wav2, 'g')
#plt.plot(sin_wav3, 'y')
plt.show()
