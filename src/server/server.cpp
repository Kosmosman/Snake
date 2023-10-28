//
// Created by Joaquina Daeron on 10/28/23.
//

#include "server.h"
#include <thread>
#include <iostream>

namespace joaquind {
    void Server::Connect() {
        NewConnection();
        io_.run();
    }

    void Server::NewConnection() {
        auto new_socket = std::make_shared<asio::ip::tcp::socket>(io_);
        acceptor_.async_accept(*new_socket, [this, new_socket](const asio::error_code& er) {
            std::cout << "New connect\n";
            if (!er) Start(new_socket);
            NewConnection();
        });
    }

    void Server::Start(socket_ptr s) {

        s->async_read_some(asio::buffer(buff_, 1), [this, s](const asio::error_code &er, size_t bytes) {
            if (buff_[0]) std::cout << "Client input " << buff_[0] << '\n';
            Start(s);
        });
    }
} // joaquind