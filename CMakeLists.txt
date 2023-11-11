cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TEST "Build test for project" ON)

add_subdirectory(src)
add_subdirectory(include)
add_executable(Main main.cpp)

target_link_libraries(Main PUBLIC Server GameLogic)

if (BUILD_TEST)

    include(FetchContent)

    set(FETCHCONTENT_QUIET OFF)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(Tests
            ${CMAKE_CURRENT_SOURCE_DIR}/tests/logic_test.cpp)

    target_link_libraries(Tests PUBLIC GameLogic gtest gtest_main)
    target_include_directories(Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/logic)
endif ()