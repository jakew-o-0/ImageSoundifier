#include "pool_utils.h"
#include <stdlib.h>
#include <stdio.h>

void append_chord(chord chord_instance, chord_pool* chordPool) {
	chordPool->size++;
	chord* _cptr = (chord*)realloc(chordPool->chord_ptr, (sizeof(chord) * chordPool->size));

	if(!_cptr) {
		printf("something went horribly wrong\n");
		exit(1);
	}else
		chordPool->chord_ptr = _cptr;

	for(int i = 0; i < TABLE_SIZE; i++)
		chordPool->chord_ptr[chordPool->size - 1].wavetable[i] = chord_instance.wavetable[i];
}
