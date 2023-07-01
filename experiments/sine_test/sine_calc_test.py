import matplotlib.pyplot as plt

with open("/home/jake/image_soundifier/wav_table", 'rb') as wav_table:
    sin_wav = list(wav_table.read())

plt.plot(sin_wav)
plt.show()
