cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(include)
add_executable(Main main.cpp)

target_link_libraries(Main PUBLIC Server GameLogic)