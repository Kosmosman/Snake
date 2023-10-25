cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_library(Asio INTERFACE)
target_include_directories(Asio INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/asio-1.28.0/include")