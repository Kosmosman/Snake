cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_library(Server STATIC server/server.cpp server/server.h)
target_link_libraries(Server PUBLIC Asio)
target_include_directories(Server PRIVATE server)