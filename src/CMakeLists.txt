cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(view)

add_library(Client client/client.cpp client/client.h)
target_link_libraries(Client PUBLIC Asio Window)
target_include_directories(Client PUBLIC client render)