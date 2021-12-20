cmake_minimum_required(VERSION 3.21)
project(mephi_lab_graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(mephi_lab_graph main.cpp Graph.hpp functions.hpp tests.hpp)
