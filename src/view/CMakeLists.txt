cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_library(glad
        lib/glad/src/gl.c
        lib/glad/include/glad/gl.h
        lib/glad/include/KHR/khrplatform.h
        )

add_library(Window INTERFACE
        window/window.h
        window/abstract_window.h window/windows_fabric.h window/observer.h window/interpreter.h window/types.h)

target_link_libraries(Window INTERFACE imguiLib glad)
target_include_directories(Window INTERFACE lib/imgui window lib/glad/include)