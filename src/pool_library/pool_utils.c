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

	chordPool->chord_ptr[chordPool->size - 1].chord_pixel.B = chord_instance.chord_pixel.B;
	chordPool->chord_ptr[chordPool->size - 1].chord_pixel.G = chord_instance.chord_pixel.G;
	chordPool->chord_ptr[chordPool->size - 1].chord_pixel.R = chord_instance.chord_pixel.R;

	for(int i = 0; i < TABLE_SIZE; i++)
		chordPool->chord_ptr[chordPool->size - 1].wavetable[i] = chord_instance.wavetable[i];
}
