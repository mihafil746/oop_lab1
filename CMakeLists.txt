cmake_minimum_required(VERSION 3.16)

project(lab1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

add_library(lib_xml lib/xml.h lib/xml.cpp)

add_subdirectory(tests)

link_libraries(lib_xml readline)

add_executable(bin main.cpp)