cmake_minimum_required(VERSION 3.10)

project(advent_2024)

include_directories(src)

add_executable(advent_1 src/advent_1.cpp src/advent_1.hpp src/advent_common.cpp)
add_executable(advent_2 src/advent_2.cpp src/advent_2.hpp src/advent_common.cpp)
add_executable(advent_3 src/advent_3.cpp src/advent_3.hpp src/advent_common.cpp)

# Copy the "res" folder into the binary folder
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
