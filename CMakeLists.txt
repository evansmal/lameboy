project(lameboy)
cmake_minimum_required(VERSION 3.19)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(liblameboy src/cpu.cpp src/decoder.cpp src/cartridge.cpp)
target_include_directories(liblameboy PUBLIC src )
target_compile_options(liblameboy PUBLIC -O1 -Wall -std=c++20 )

add_executable(lameboy src/main.cpp)
target_link_libraries(lameboy PUBLIC liblameboy )
target_compile_options(lameboy PUBLIC -O1 -Wall -std=c++20 )

add_executable(test-mts test/test_mts.cpp)
target_link_libraries(test-mts PUBLIC liblameboy )
target_compile_options(test-mts PUBLIC -O1 -Wall -std=c++20 )
