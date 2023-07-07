#ifndef __BMP_PARSE__
#define __BMP_PARSE__
#include "../utils.h"


#pragma pack(push, 1)
typedef struct {
	unsigned short filetype;
	unsigned int size;
	unsigned int _padding;
	unsigned int pixel_offset;
} bmp_fileHeader;


typedef struct {
	unsigned char B;
	unsigned char G;
	unsigned char R;
} pixel;
#pragma pack(pop)

typedef struct {
	pixel chord_pixel;
	float wavetable[TABLE_SIZE];
} chord;

typedef struct {
	unsigned int header_size;
	unsigned int image_width;
	unsigned int image_hight;
	unsigned short planes;
	unsigned short bpp;
	unsigned int compression;
	unsigned long _padding;
	unsigned int total_colours;
	unsigned int __pading;
} bmp_infoHeader;



typedef struct {
	bmp_fileHeader fileHeader;
	bmp_infoHeader infoHeader;
} bmp_header;


void gen_noise(float* wave_table, int table_size, char* path);
void get_wave_table(float* wave_table, int table_size, char* path);


#endif
