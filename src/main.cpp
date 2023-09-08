#include "../headers/ImageParser.hpp"
#include <fstream>
#include <iostream>
#include <ranges>

void writeChordTableToFile(std::vector<chord>& ChordTable);


int main() {
    std::vector<chord> ChordTable;
    std::string path = "/home/jake/projects/ImageSoundifier/resorces/test_image.bmp";

    ImageParser parser = ImageParser(path);
    parser.GenCordProgression(ChordTable);

    writeChordTableToFile(ChordTable);
    return 1;
}

void writeChordTableToFile(std::vector<chord>& ChordTable) {
    using namespace std::ranges;
    std::ofstream output("/home/jake/projects/ImageSoundifier/resources/testwavetable.txt");
    for(int i : iota_view(0, 10) ) {
        for(int j : iota_view(0, TABLE_SIZE)) {
            output << ChordTable[i].wavetable[j] << std::endl;
        }
    }
}