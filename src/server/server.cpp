//
// Created by Joaquina Daeron on 10/28/23.
//

#include "server.h"
#include "joinable_thread.h"
#include <thread>
#include <iostream>

namespace joaquind {
    void Server::Connect() {
        asio::io_context io;
        asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 8080);
        asio::ip::tcp::acceptor acceptor(io, ep);
        size_t count_of_peers{};

        while (count_of_peers < 2) {
            auto socket = std::make_shared<asio::ip::tcp::socket>(io);
            acceptor.accept(*socket);
            Jthread jthread([this] { Start(); });
            ++count_of_peers;
        }
    }

    void Server::Start() {
        std::cout << "New connect\n";
        while (true);
    }
} // joaquind