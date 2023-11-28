cmake_minimum_required(VERSION 3.15)
project(Example)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FETCHCONTENT_DECLARE(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)

FetchContent_MakeAvailable(glfw)

list(APPEND CMAKE_MODULE_PATH "${glfw_SOURCE_DIR}")

add_library(imguiLib
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_internal.h
        imgui_tables.cpp
        imgui_widgets.cpp
        imconfig.h
        imgui_draw.cpp
        imgui_impl_glfw.cpp
        imgui_impl_glfw.h
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3.h
        imgui_impl_opengl3_loader.h
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        )

target_link_libraries(imguiLib PUBLIC glfw)

find_package(OpenGL REQUIRED)
