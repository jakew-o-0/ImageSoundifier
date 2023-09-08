import matplotlib.pyplot as plt

WaveTable = []
with(open("/home/jake/projects/ImageSoundifier/resorces/testwavetable.txt", 'r') as WTFile):
    for i in WTFile:
        WaveTable.append( float(i) )
print(WaveTable)
max = 0
min = 10
for i in WaveTable:
    if(i > max):
        max = i

    if(i < min):
        min = i

print("max: ", max)
print("min: ", min)


plt.plot(WaveTable)
plt.show()