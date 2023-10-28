cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_executable(Server server/server.cpp server/server.h)
target_link_libraries(Server PRIVATE Asio)
target_include_directories(Server PRIVATE server)
target_include_directories(Server PRIVATE "${CMAKE_SOURCE_DIR}/include/asio-12.8.0/include")

add_library(Logic INTERFACE settings)
target_include_directories(Logic INTERFACE settings)