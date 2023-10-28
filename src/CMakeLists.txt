cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_library(Client client/client.cpp client/client.h)
target_include_directories(Client PUBLIC client)