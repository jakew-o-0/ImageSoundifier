cmake_minimum_required(VERSION 3.26)
project(ImageSoundifier)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ImageSoundifier ${SRC_FILES})
target_include_directories(ImageSoundifier PUBLIC headers)
find_package(portaudio)
target_link_libraries(ImageSoundifier PUBLIC portaudio "-lrt -lm -lasound -pthread")