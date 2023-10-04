cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(settings)

add_executable(Main main.cpp)
