CC = gcc
CFLAGS = -lrt -lm -lasound -ljack -pthread
SOURCES = $(shell find ./src -name '*.c')
HEADERS = $(shell find ./src -name '*.h')
RESORCES = resorces/libportaudio.a

image_soundifier:
	$(CC) $(CFLAGS) $(SOURCES) $(HEADERS) $(RESORCES) -o $@
