cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_library(Window INTERFACE
        window/window.h
        )

target_link_libraries(Window INTERFACE imguiLib)
target_include_directories(Window INTERFACE lib/imgui window)