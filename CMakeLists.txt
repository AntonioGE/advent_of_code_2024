cmake_minimum_required(VERSION 3.10)

project(advent_2024)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(advent_1 src/advent_1.cpp src/advent_1.hpp src/advent_common.cpp)
add_executable(advent_2 src/advent_2.cpp src/advent_2.hpp src/advent_common.cpp)
add_executable(advent_3 src/advent_3.cpp src/advent_3.hpp src/advent_common.cpp)
add_executable(advent_4 src/advent_4.cpp src/advent_4.hpp src/advent_common.cpp)
add_executable(advent_5 src/advent_5.cpp src/advent_5.hpp src/advent_common.cpp)
add_executable(advent_6 src/advent_6.cpp src/advent_6.hpp src/advent_common.cpp)
add_executable(advent_7 src/advent_7.cpp src/advent_7.hpp src/advent_common.cpp)
add_executable(advent_8 src/advent_8.cpp src/advent_8.hpp src/advent_common.cpp)
add_executable(advent_9 src/advent_9.cpp src/advent_9.hpp src/advent_common.cpp)
add_executable(advent_10 src/advent_10.cpp src/advent_10.hpp src/advent_common.cpp)
add_executable(advent_11 src/advent_11.cpp src/advent_11.hpp src/advent_common.cpp)
add_executable(advent_12 src/advent_12.cpp src/advent_12.hpp src/advent_common.cpp)

# Copy the "res" folder into the binary folder
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
