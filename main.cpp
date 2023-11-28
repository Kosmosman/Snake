//
// Created by Joaquina Daeron on 10/4/23.
//

#include "client.h"
#include "window.h"

int main() {
    joaquind::Client client;
    joaquind::Window w;
    w.Init();
    client.Connect();
    return 0;
}