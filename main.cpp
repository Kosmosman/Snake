//
// Created by Joaquina Daeron on 10/4/23.
//

#include "client.h"
#include "window.h"

int main() {
    joaquind::MainWindow w;
    w.Init();
    joaquind::Client client;
    client.AddObserver(&w);
    std::thread t{[&]() { client.Connect(); }};
    t.detach();
    w.Start();
    return 0;
}