CC = gcc
CFLAGS = -lrt -lm -lasound -ljack -pthread
CHEADER = $(wildcard src/*.h)
SRCS = $(wildcard src/*.c)
RESORCES = resorces/libportaudio.a

image_soundifier: $(SRCS)
	$(CC) $(CFLAGS) $^ $(CHEADER) $(RESORCES) -o $@
