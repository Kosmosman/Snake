//
// Created by Joaquina Daeron on 10/28/23.
//

#include "server.h"
#include <thread>
#include <iostream>
#include <chrono>

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
            } else {
                new_socket->close();
            }
            NewConnection();
        });
    }

    void Server::Start(socket_ptr s) {
        auto id = clients_[s];
        s->async_read_some(asio::buffer(buff_ + id, 1), [this, s, id](const asio::error_code &er, size_t bytes) {
            DataUpdate(id);
            Start(s);
        });
    }

    void Server::AddNewClient(socket_ptr socket) {
        if (count_of_clients.load() == max_count_of_clients) return;
        clients_[socket] = count_of_clients.fetch_add(1);
        Start(std::move(socket));
    }

    void Server::DataUpdate(size_t id) {
        mutex_.lock();
        auto field = g_->UpdateField(buff_[id], id);
        mutex_.unlock();
        for (const auto &i: clients_) {
            i.first->write_some(asio::buffer(field));
        }
    }

} // joaquind