cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_library(Utility INTERFACE utility)
target_include_directories(Utility INTERFACE utility)

add_library(
        GameLogic INTERFACE
        logic/configurations.h
        logic/field.h
        logic/game.h
        logic/meal.h
        logic/snake.h
)

add_library(Server server/server.cpp server/server.h)
target_link_libraries(Server PUBLIC Asio Utility GameLogic)
target_include_directories(Server PUBLIC server)
target_include_directories(Server PUBLIC logic)
target_include_directories(Server PRIVATE utility)