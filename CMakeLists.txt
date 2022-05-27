cmake_minimum_required(VERSION 3.16.3)
project(test_matrix_mult)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
add_executable(test_matrix_mult main.cpp matrix.h matrix.cpp)
target_link_libraries (test_matrix_mult ${CMAKE_THREAD_LIBS_INIT})
