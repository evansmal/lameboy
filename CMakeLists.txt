project(lameboy)
cmake_minimum_required(VERSION 3.15)

add_executable(lameboy src/main.cpp)
target_compile_options(lameboy PUBLIC -Wall -std=c++20 )

