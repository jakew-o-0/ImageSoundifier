#include "parse_bmp.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void parse_file(float *wave_table, char *path) {
	FILE* fptr = fopen(path, "rb");
	if(fptr == NULL) {
		printf("error opening file");
		exit(1);
	}

	bmp_fileHeader fileHeader;
	fread(&fileHeader, sizeof(bmp_fileHeader), 1, fptr);
	/*
	printf("%d\n%d\n%d\n", 	fileHeader.filetype, 
				fileHeader.pixel_offset, 
				fileHeader.size);
	*/

	bmp_infoHeader infoHeader;
	fread(&infoHeader, sizeof(bmp_infoHeader), 1, fptr);
	/*
	printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n", 	infoHeader.header_size,
						infoHeader.bpp, 
						infoHeader.compression,
						infoHeader.image_hight, 
						infoHeader.image_width, 
						infoHeader.total_colours, 
						infoHeader.planes);
	*/

	
	int image_size = infoHeader.image_hight * infoHeader.image_width;
	char pix_table[image_size];

	fseek(fptr, fileHeader.pixel_offset, SEEK_SET);
	fread(pix_table, sizeof(char), image_size, fptr);



	for(int i = 0; i < image_size; i += 3) {
		
		printf("B:%x G:%x R:%x\t", pix_table[i], pix_table[i + 1], pix_table[i + 2]);
		if( i % 4 == 3 && i > 0)
			printf("\n");
	}

}
