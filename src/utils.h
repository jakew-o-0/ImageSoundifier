#ifndef _UTILS_
#define _UTILS_


#define TABLE_SIZE 2048
#define SAMPLE_RATE 44100




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





typedef struct {
	chord* chord_ptr;
	int size;
} chord_pool;


#endif
