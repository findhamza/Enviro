cmake_minimum_required(VERSION 3.16)
project(LSystem)
project(FSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -s -O3")

add_executable(LSystem src/Testing/LSystem/lsys.cpp src/Testing/LSystem/Linden.cpp src/Testing/LSystem/Linden.h)
add_executable(FSM src/Testing/FSM/fsm.cpp)


find_package(SDL2 REQUIRED)
add_executable(Display src/Testing/SDL/Display.cpp)