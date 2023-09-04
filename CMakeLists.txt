cmake_minimum_required(VERSION 3.27.0)
project(ImageSoundifier VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ImageSoundifier  ${SRC_FILES} )
target_include_directories(ImageSoundifier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
