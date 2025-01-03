cmake_minimum_required(VERSION 3.10)

project(advent_2024)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

foreach(i RANGE 1 17)
    add_executable(advent_${i} src/advent_${i}.cpp src/advent_${i}.hpp src/advent_common.cpp)
endforeach()

# Copy the "res" folder into the binary folder
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
