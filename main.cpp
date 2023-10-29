//
// Created by Joaquina Daeron on 10/4/23.
//

#include "server.h"
#include "game.h"

int main() {
    joaquind::Field field(30, 30);
    std::vector<joaquind::Snake> snakes{ joaquind::Snake({5, 5}),  joaquind::Snake({25, 25})};
    joaquind::Meal meal;
    joaquind::Game g(&field, &snakes, &meal);
    joaquind::Server s(&g);
    s.Connect();
    return 0;
}