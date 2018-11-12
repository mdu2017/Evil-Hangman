# Evil-Hangman
Implementing Evil Hangman

Setting up the SDL Plotter in CLion:
1. Copy and paste this into the CMakeLists.txt

===================================================================
cmake_minimum_required(VERSION 3.9)

project(GroupProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(GroupProject main.cpp SDL_Plotter.h)
target_link_libraries(GroupProject SDL2main SDL2 SDL2_mixer)
===================================================================

To run the program:
1. Go into directory of your choice and clone the repository
2. Open the project folder in CLion and run the program.

*Note: move input files into the CMake-Debug folder to read them using ifstream
