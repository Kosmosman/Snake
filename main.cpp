//
// Created by Joaquina Daeron on 10/4/23.
//

#include "client.h"
#include "window.h"

int main() {
    joaquind::Client client;
    joaquind::MainWindow w;
    std::thread t{[&]() { client.Connect(); }};
    t.detach();
    w.Init();
    return 0;
}