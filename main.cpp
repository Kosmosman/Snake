//
// Created by Joaquina Daeron on 10/4/23.
//

#include "client.h"
#include "window.h"

int main() {
    joaquind::MainWindow w;
    joaquind::Client client;
    std::thread t{[&]() { client.Connect(); }};
    t.detach();
    w.Init();
    return 0;
}