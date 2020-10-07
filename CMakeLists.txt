cmake_minimum_required(VERSION 3.15)
project(NokiaInternship)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(googletest/googletest/include googletest/googletest)

add_executable(NokiaInternship main.cpp table.cpp)
add_executable(tableTest test.cpp table.cpp)

target_link_libraries(tableTest gtest gtest_main)