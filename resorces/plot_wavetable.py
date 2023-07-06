import matplotlib.pyplot as plt

wavtab:float = []
with open("./wavetable", "rb") as wavetable:
    wavtab = list(wavetable.read(wavetable.__sizeof__()))
    print(wavtab)

plt.plot(wavtab)
plt.show()