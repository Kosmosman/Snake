//
// Created by Joaquina Daeron on 10/4/23.
//

#include "game.h"

int main() {
    std::cout << "Input height and width of field: ";
    joaquind::size_t h, w;
    std::cin >> h >> w;
    joaquind::Field f (h, w);
    joaquind::Snake s(std::pair(h, w));
    joaquind::Meal m;
    joaquind::Game g(&f, &s, &m);
    std::cout << "Press any key for start\n";
    g.start();
    return 0;
}