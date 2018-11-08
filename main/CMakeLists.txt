cmake_minimum_required(VERSION 3.9)

project(evilHangman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(evilHangman main.cpp SDL_Plotter.h)
target_link_libraries(evilHangman SDL2main SDL2 SDL2_mixer)