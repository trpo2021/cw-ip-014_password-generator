cmake_minimum_required(VERSION 3.17)
project(PGen)

set(CMAKE_CXX_STANDARD 11)

include_directories(3rdparty)
add_executable(PGen main.cpp)