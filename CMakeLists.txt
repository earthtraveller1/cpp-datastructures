cmake_minimum_required(VERSION 3.13)

project("cpp-datastructures")

set(CMAKE_CXX_STANDARD 20)

add_executable("sandbox" "src/main.cpp")

target_include_directories("sandbox" PRIVATE "${CMAKE_SOURCE_DIR}/include")
