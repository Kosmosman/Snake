//
// Created by Joaquina Daeron on 10/4/23.
//

#include "server.h"
#include "game.h"

int main() {
    joaquind::Field field(30, 30);
    joaquind::SnakeBuilder snake_builder;
    joaquind::Meal meal;
    joaquind::Game g(&field, &snake_builder, &meal);
    joaquind::Server s(&g);
    s.Connect();
    return 0;
}