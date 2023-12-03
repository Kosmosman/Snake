//
// Created by Joaquina Daeron on 10/4/23.
//

#include "server.h"
#include "game.h"

int main() {
    int n{40}, m{40};
    joaquind::ObjectManager om;
    joaquind::Game g(&om, {n, m});
    joaquind::Server s(&g);
    s.Connect();
    return 0;
}