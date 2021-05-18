cmake_minimum_required(VERSION 3.17)
project(PGen)

set(CMAKE_CXX_STANDARD 11)
set(PASS_GEN_SRCS ${CMAKE_SOURCE_DIR}/PasswordGenerator.cpp ${CMAKE_SOURCE_DIR}/PasswordGenerator.h)
set(INCLUDE_FOLDERS 3rdparty ${CMAKE_SOURCE_DIR})

add_library(PasswordGeneratorLib ${CMAKE_SOURCE_DIR}/PasswordGenerator.cpp ${CMAKE_SOURCE_DIR}/PasswordGenerator.h)
target_include_directories(PasswordGeneratorLib PUBLIC ${INCLUDE_FOLDERS})

add_executable(PGen ${CMAKE_SOURCE_DIR}/main.cpp)
target_link_libraries(PGen PasswordGeneratorLib)

add_executable(PGenTests ${CMAKE_SOURCE_DIR}/test/PGenTests.cpp ${CMAKE_SOURCE_DIR}/test/PasswordGeneratorTests.h)
target_link_libraries(PGenTests PasswordGeneratorLib)