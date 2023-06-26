#ifndef __BMP_PARSE__
#define __BMP_PARSE__


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



void parse_file(float* wave_table, char* path);


#endif
