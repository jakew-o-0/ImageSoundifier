#include "../headers/ImageParser.hpp"

#include <fstream>
#include <iostream>

int main(void) {
    std::vector<chord> ChordTable;
    std::string path = "/home/jake/projects/image_soundifier/resorces/test_image.bmp";
    ImageParser parser = ImageParser(path);
    parser.GenCordProgression(ChordTable);
    return 1;
}

void writeChordTableToFile(std::vector<chord>& ChordTable) {
    std::ofstream output("/home/jake/projects/image_soundifier/resources/testwavetable.txt");
    for(int i=0; i < ChordTable.size(); i++) {
        for(int j=0; j < TABLE_SIZE; j++) {
            output << ChordTable[i].wavetable[j] << "\n";
        }
    }
}