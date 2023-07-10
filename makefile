CC = gcc
CFLAGS = -g -lrt -lm -lasound -ljack -pthread -lpulse
SOURCES = $(shell find ./src -name '*.c')
HEADERS = $(shell find ./src -name '*.h')
RESORCES = resorces/libportaudio.a

image_soundifier:
	$(CC) $(CFLAGS) $(SOURCES) $(HEADERS) $(RESORCES) -o $@
