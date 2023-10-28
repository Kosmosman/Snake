//
// Created by Joaquina Daeron on 10/28/23.
//

#include "server.h"

namespace joaquind {
    void Server::Connect() {
        asio::io_context io;
        asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 8080);
        asio::ip::tcp::acceptor acceptor(io, ep);
    }
} // joaquind