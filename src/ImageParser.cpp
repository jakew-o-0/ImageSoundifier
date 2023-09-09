#include "../headers/ImageParser.hpp"
#include <fstream>
#include <cmath>
#include <iostream>

ImageParser::ImageParser(std::string& path) {
    // read bitmap into a buffer && allocate that buffer into ImageBuffer
    std::ifstream input(path, std::ios::binary);
    ImageBuffer.assign(std::istreambuf_iterator<char>(input), {});

    // get the offset for the pixel bytes
    // by combining the 4 bytes that make the in for the offset to the start of the pixels
    std::vector<unsigned char> buffSlice(ImageBuffer.begin() + 10,
                                         ImageBuffer.begin() + 10 + 4);
    ImageOffset = 0;
    int shiftSize = 32;
    for (auto i : buffSlice) {
        ImageOffset |= (i << shiftSize);
        shiftSize -= 8;
    }

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
            double freqency = calcFrequency(currPix.B);
            // ensure the amplitude is within the range -1 to 1
            double amplitude = 2. * currPix.G / 255 - 1;

            // create wave
            currCord.wavetable.resize(TABLE_SIZE);
            for(int n = 0; n < TABLE_SIZE; n++) {
                double point = calcWavePoint(freqency, amplitude, currPix.R, n);
                currCord.wavetable[n] += point;
            }

            double max = 0;
            double min = 10;
            for(auto n : currCord.wavetable) {
                if(n > max) { max = n; }
                if(n < min) { min = n; }
            }

            for(int n = 0; n < TABLE_SIZE; n++) {
                currCord.wavetable[n] *= 2;
                currCord.wavetable[n] /= max - min;
            }

            // add wave to the chord wavetable
            ChordTable.push_back(currCord);
        }
    }
}


double ImageParser::calcFrequency(double key) {
    return 13.75 * pow(2.0, (1.0/12.0) * key);
}

double ImageParser::calcWavePoint(double f, double a, double p, int n) {
	return a * sin((2. * M_PI * f * (n / 44100.)) + p);
}