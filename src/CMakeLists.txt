cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_library(Logic INTERFACE settings)
target_include_directories(Logic INTERFACE settings)