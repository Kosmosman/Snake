//
// Created by Joaquina Daeron on 10/4/23.
//

#include "src/settings/configurates.h"

int main() {
    joaquind::field<30, 50> f;
    joaquind::snake s(f);
    joaquind::game g(f, s);
    g.start();
    return 0;
}