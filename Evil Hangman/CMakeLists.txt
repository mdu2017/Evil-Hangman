cmake_minimum_required(VERSION 3.9)

project(Eviler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(Eviler main.cpp SDL_Plotter.h line.h rectangle.h color.h point.h shapes.h letters.h)
target_link_libraries(Eviler SDL2main SDL2 SDL2_mixer)