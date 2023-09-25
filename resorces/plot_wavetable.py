import matplotlib.pyplot as plt

WaveTable = []
with(open("/home/jake/code/ImageSoundifier/resorces/testwavetable.txt", 'r') as WTFile):
    for i in WTFile:
        WaveTable.append( float(i) )

plt.plot(WaveTable)
plt.show()
