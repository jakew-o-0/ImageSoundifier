#include "parse_bmp.h"
#include "../pool_library/pool_utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float calc_wav_point(float f, float a, float p, int n);
float calc_freq(int key);



void gen_noise(float* wave_table, int table_size, char* path) {
	FILE* fptr = fopen(path, "rb");
	if(fptr == NULL) {
		printf("error opening file");
		exit(1);
	}

	bmp_fileHeader fileHeader;
	fread(&fileHeader, sizeof(bmp_fileHeader), 1, fptr);

	bmp_infoHeader infoHeader;
	fread(&infoHeader, sizeof(bmp_infoHeader), 1, fptr);
	
	int image_size = infoHeader.image_hight * infoHeader.image_width;
	fseek(fptr, fileHeader.pixel_offset, SEEK_SET);

	for(int i = 0; i < image_size; i++ ) {
		pixel pix;
		fread(&pix, sizeof(pixel), 1, fptr);

		int key = ((pix.B + pix.G + pix.R) / 3) % 12;
		calc_freq(key);
		for(int j = 0; j < table_size; j++) {
			wave_table[j] += calc_wav_point(key, 0.5, 0, j);
		}
	}
}





void gen_chords(chord_pool* chord_pool, char* path) {
	FILE* fptr = fopen(path, "rb");
	if(fptr == NULL) {
		printf("error opening file");
		exit(1);
	}

	bmp_fileHeader fileHeader;
	fread(&fileHeader, sizeof(bmp_fileHeader), 1, fptr);

	bmp_infoHeader infoHeader;
	fread(&infoHeader, sizeof(bmp_infoHeader), 1, fptr);
	
	int image_size = infoHeader.image_hight * infoHeader.image_width;
	fseek(fptr, fileHeader.pixel_offset, SEEK_SET);

	
	for(int i; i < image_size; i++) {
		chord _temp_chord;
		fread(&_temp_chord.chord_pixel, sizeof(pixel), 1, fptr);

		int chord_size = _temp_chord.chord_pixel.B % 5;
		float _wavetable[TABLE_SIZE];

		for(; i < chord_size; i++) {
			fread(&_temp_chord.chord_pixel, sizeof(pixel), 1, fptr);
			int key = ((_temp_chord.chord_pixel.B + _temp_chord.chord_pixel.G + _temp_chord.chord_pixel.R) / 3) % 12;
			calc_freq(key);
			for(int j = 0; j < TABLE_SIZE; j++) {
				_wavetable[j] += calc_wav_point(key, 0.5, 0, j);
			}
		}
		append_chord(_temp_chord, chord_pool);
	}
}






float calc_freq(int key) {
	return 110 * pow(2.0, (1.0/12) * key);
}



float calc_wav_point(float f, float a, float p, int n) {
	return a * sin(((2. * M_PI) * f * (float)n / 44100.) + p);
}
