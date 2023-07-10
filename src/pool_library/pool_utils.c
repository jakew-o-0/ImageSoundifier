#include "pool_utils.h"
#include <stdlib.h>
#include <stdio.h>

void append_chord(chord chord_instance, chord_pool* chordPool) {
	chordPool->size++;
	printf("\nchordPool length: %d\n", chordPool->size);
	chord* _cptr = realloc(chordPool->chord_ptr, (sizeof(chord) * chordPool->size));
	printf("chordPool size after realloc: %ld\n\n", (sizeof(chord) * chordPool->size));

	if(!_cptr) {
		printf("something went horribly wrong\n");
		exit(1);
	}else
		chordPool->chord_ptr = _cptr;


	for(int i = 0; i < TABLE_SIZE; i++)
		chordPool->chord_ptr[chordPool->size].wavetable[i] = chord_instance.wavetable[i];

	for(int i = 0; i < TABLE_SIZE; i++)
		printf("%f", chordPool->chord_ptr[chordPool->size].wavetable[i] = chord_instance.wavetable[i]);
}
