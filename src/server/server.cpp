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
        acceptor_.async_accept(*new_socket, [this, new_socket](const asio::error_code &er) {
            std::cout << "New connect\n";
            if (!er) {
                AddNewClient(new_socket);
            }
            NewConnection();
        });
    }

    void Server::Start(socket_ptr s) {
        s->async_read_some(asio::buffer(buff_, 1), [this, s](const asio::error_code &er, size_t bytes) {
            if (buff_[0]) std::cout << "Client input " << buff_[0] << '\n';
            auto field = g_->UpdateField(buff_[0]);
            s->write_some(asio::buffer(field));
            Start(s);
        });
    }

    void Server::AddNewClient(socket_ptr socket) {
        if (count_of_clients.load() == max_count_of_clients) return;
        clients_[socket] = count_of_clients.fetch_add(1);
        Start(std::move(socket));
    }

} // joaquind