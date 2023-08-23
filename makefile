CC = g++
CFLAGS = -g -lrt -lm -lasound -ljack -pthread -lpulse
SOURCES = $(shell find ./src -name '*.cpp')
HEADERS = $(shell find ./src -name '*.hpp')
RESORCES = resorces/libportaudio.a

image_soundifier:
	$(CC) $(CFLAGS) $(SOURCES) $(HEADERS) $(RESORCES) -o $@
