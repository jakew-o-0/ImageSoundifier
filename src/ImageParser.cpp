#include "../headers/ImageParser.hpp"
#include <fstream>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ranges>

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


bool ImageParser::GenChord( std::queue<double>& AudioBuff ) {
    namespace ranges = std::ranges;
    std::vector<double> WaveTable(TABLE_SIZE, 0);
    double min = 10, max = 0;

    for(int j = 0; j < 3; j++) {
        pixel currPix {
                ImageBuffer[ImageOffset],
                ImageBuffer[ImageOffset + 1],
                ImageBuffer[ImageOffset + 2]
        };

        // define wave rules from the pixel
        double freqency = calcFrequency(currPix.B);
        // ensure the amplitude is within the range -1 to 1
        double amplitude = 2. * currPix.G / 255 - 1;

        // create wave
        for(int n: ranges::iota_view(0, TABLE_SIZE)) {
            WaveTable[n] += calcWavePoint(freqency, amplitude, currPix.R, n);

            min = n < min ? n : min;
            max = n > max ? n : max;
        }
    }

    // map the wave between the values of 1 and -1
    std::for_each(WaveTable.begin(), WaveTable.end(),
                  [&max, &min](double n){ return (min - max)/n; });

    std::ofstream file("../resorces/testwavetable.txt", std::ios::out | std::ios::app);
    for(auto n: WaveTable) {
        AudioBuff.push(n);
        file << n << std::endl;
    }


    constexpr int offset = (3*4)*3;
    ImageOffset += offset;

    if(ImageOffset > (ImageBuffer.size() - 3)) {
        return false;
    }
    return true;
}


double ImageParser::calcFrequency(double key) {
    return 13.75 * pow(2.0, (1.0/12.0) * key);
}

double ImageParser::calcWavePoint(double f, double a, double p, int n) {
	return a * sin((2. * M_PI * f * (n / 44100.)) + p);
}