#ifndef __BMP_PARSE__
#define __BMP_PARSE__
#include "../utils.h"

void gen_noise(float* wave_table, int table_size, char* path);
void gen_chords(chord_pool* chord_pool, char* path);
void get_wave_table(float* wave_table, int table_size, char* path);


#endif
