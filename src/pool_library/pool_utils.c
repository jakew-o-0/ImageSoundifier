#include "../parse_bitmap/parse_bmp.h"
#include "pool_utils.h"
#include <stdlib.h>
void append_chord(chord chord_instance, chord_pool* chordPool) {
	chordPool->chord_ptr = realloc(chordPool->chord_ptr, chordPool->size + sizeof(chord));
	chordPool->size++;
	chordPool->chord_ptr[chordPool->size]
	for(int i = 0; i < TABLE_SIZE; i++) {

	}
}
