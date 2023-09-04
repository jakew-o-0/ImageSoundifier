#include "../headers/ImageParser.hpp"
#include <fstream>
#include <cmath>
#include <iostream>

ImageParser::ImageParser(std::string path) {
    // read bitmap into a buffer
    std::ifstream input(path, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    // allocate that buffer into ImageBuffer
    std::copy(buffer.begin(), buffer.end(), ImageBuffer.begin());

    // get the offset for the pixel bytes
    std::vector<unsigned char> buffSlice(buffer.begin() + 10, buffer.end());
    int shiftSize = 8 * 4;
    for (auto i : buffSlice)
    {
        ImageOffset |= (i << shiftSize);
        shiftSize -= 8;
    }

}

ImageParser::~ImageParser() {
}


void ImageParser::GenCordProgression(std::vector<chord> &ChordTable) {
    //itterating through 4 pixel at a time (4 * 3 bytes)
    for(int i = 0; i < ((int)ImageBuffer.size() / (4*3)); i++) {
        int BuffOffset = (i * (3 * 4)) + ImageOffset;

        // allocate the size of the wavetable as 0s
        chord currCord;
        currCord.wavetable.assign(0, TABLE_SIZE);
        currCord.chord_pixel.B = ImageBuffer[BuffOffset];
        currCord.chord_pixel.G = ImageBuffer[BuffOffset + 1];
        currCord.chord_pixel.R = ImageBuffer[BuffOffset + 2];

        // itterate through the remaning 3 pixels to create the chord wavetable
        for(int j = 0; j < 3; j++) {
            BuffOffset += 3;
            pixel currPix;
            currPix.B = ImageBuffer[BuffOffset];
            currPix.G = ImageBuffer[BuffOffset + 1];
            currPix.R = ImageBuffer[BuffOffset + 2];

            // define wave rules from the pixel
            float freqency = calcFrequency((float)currPix.B);
            // ensure the amplitude is within the range -1 to 1
            float amplitude = 2 * currPix.G / 255 - 1;

            // create wave
            for(int n = 0; n < TABLE_SIZE; n++) {
                float point =  calcWavePoint(freqency, amplitude, currPix.R, n);
                currCord.wavetable[n] += point;
            }

            ChordTable.push_back(currCord);
            // add wave to the chord wavetable
        }
    }
}


float ImageParser::calcFrequency(float key) {
    return 13.75 * powf(2.0, (1.0/12.0) * key);
}


float ImageParser::calcWavePoint(float f, float a, float p, int n) {
	return a * sinf((2. * M_PI * f * ((float)n / 44100.)) + p);
}