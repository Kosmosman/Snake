//
// Created by Joaquina Daeron on 10/28/23.
//

#include "client.h"
#include "asio.hpp"

namespace joaquind {
    void Client::Connect() {
        asio::io_context io;
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 8080);
        asio::ip::tcp::socket s(io);
        s.connect(ep);
    }
} // joaquind