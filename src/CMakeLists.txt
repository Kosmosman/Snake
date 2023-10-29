cmake_minimum_required(VERSION 3.15)
project(Snake)
set(CMAKE_CXX_STANDARD 20)

add_library(Utility INTERFACE utility)
target_include_directories(Utility INTERFACE utility)

add_library(
        GameLogic INTERFACE
        settings/configurations.h
        settings/field.h
        settings/game.h
        settings/meal.h
        settings/snake.h
)
target_include_directories(GameLogic INTERFACE settings)

add_library(Server server/server.cpp server/server.h)
target_link_libraries(Server PUBLIC Asio Utility GameLogic)
target_include_directories(Server PUBLIC server)
target_include_directories(Server PRIVATE utility)