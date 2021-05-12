cmake_minimum_required(VERSION 3.17)
project(PGen)

set(CMAKE_CXX_STANDARD 11)

include_directories(3rdparty)
include_directories(/)
add_executable(PGen main.cpp PasswordGenerator.cpp PasswordGenerator.h)