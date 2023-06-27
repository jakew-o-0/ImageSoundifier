#include "parse_bmp.h"


int main(void) {
	float wave_table[256];
	char* path = "/home/jake/code/image_soundifier/resorces/test_image.bmp";
	parse_file(wave_table, path);

	return 0;
}
