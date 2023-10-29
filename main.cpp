//
// Created by Joaquina Daeron on 10/4/23.
//

#include "server.h"
#include "game.h"

int main() {
    joaquind::Field field(30, 30);
    joaquind::Snake snake({15, 15});
    joaquind::Meal meal;
    joaquind::Game g(&field, &snake, &meal);
    joaquind::Server s(&g);
    s.Connect();
    return 0;
}