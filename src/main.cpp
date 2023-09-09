#include "../headers/ImageParser.hpp"
#include "../headers/AudioInterface.hpp"
#include <fstream>
#include <iostream>
#include <ranges>

void writeChordTableToFile(std::vector<chord>& ChordTable);


int main() {
    std::vector<chord> ChordTable;
    std::string path = "/home/jake/projects/ImageSoundifier/resorces/MultiColouredImage.bmp";

    ImageParser parser = ImageParser(path);
    parser.GenCordProgression(ChordTable);

    auto interface = AudioInterface(ChordTable);
    interface.PlayStream();

    writeChordTableToFile(ChordTable);
    return 1;
}

void writeChordTableToFile(std::vector<chord>& ChordTable) {
    using namespace std::ranges;
    std::ofstream output("/home/jake/projects/ImageSoundifier/resorces/testwavetable.txt");
    for(int i : iota_view(0, 10) ) {
        for(int j : iota_view(0, TABLE_SIZE)) {
            output << ChordTable[i].wavetable[j] << std::endl;
        }
    }
}