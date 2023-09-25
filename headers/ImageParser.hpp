#pragma once
#include <vector>
#include <string>
#include <queue>


/*
typedef struct {
    unsigned short filetype;
    unsigned int size;
    unsigned int _padding;
    unsigned int pixel_offset;
} bmp_fileHeader;
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
    pixel chord_pixel;
    std::vector<double> wavetable;
} chord;
*/

typedef struct {
    unsigned char B;
    unsigned char G;
    unsigned char R;
} pixel;


constexpr int TABLE_SIZE = 2048;

class ImageParser {
private:
    std::vector<unsigned char> ImageBuffer {};
    int ImageBuffPtr;
    int ImageOffset;
    
public:
    explicit ImageParser(std::string& path);
    ~ImageParser() = default;
    bool GenChord( std::queue<double>& AudioBuff );
    static double calcFrequency(double key);
    static double calcWavePoint(double f, double a, double p, int n);
};