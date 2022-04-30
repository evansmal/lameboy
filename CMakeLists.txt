project(lameboy)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(lameboy src/main.cpp src/cartridge.cpp)
target_compile_options(lameboy PUBLIC -O3 -Wall -std=c++20 )

