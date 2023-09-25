#include "../headers/ImageParser.hpp"
#include "../headers/AudioInterface.hpp"
#include <fstream>
#include <iostream>
#include <ranges>



int main() {
    std::string path = "/home/jake/code/ImageSoundifier/resorces/landscape2.bmp";
    ImageParser parser = ImageParser( path );
    AudioInterface interface = AudioInterface( parser );
    interface.PlayStream();
    while(interface.IsValid){}
    return 1;
}
