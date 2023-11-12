//
// Created by Joaquina Daeron on 10/28/23.
//

#include "server.h"
#include <thread>
#include <iostream>
#include <chrono>

namespace joaquind {
    void Server::Connect() {
        HandleConnection();
        io_.run();
    }

    void Server::HandleTimeout(const asio::error_code &error, socket_ptr s) {
        if (!error) {
            HandleUpdate(std::move(s));
        } else {
            std::cout << error.message() << '\n';
        }
    }

    void Server::HandleUpdate(Server::socket_ptr s) {
        DataUpdate(s);
        clients_[s].timer->cancel();
        clients_[s].timer->expires_from_now(asio::chrono::milliseconds(1000));
        clients_[s].timer->async_wait([this, s](const asio::error_code &err) { HandleTimeout(err, s); });
    }


    void Server::HandleConnection() {
        auto new_socket = std::make_shared<asio::ip::tcp::socket>(io_);
        acceptor_.async_accept(*new_socket, [this, new_socket](const asio::error_code &error) {
            std::cout << "New connect\n";
            if (!error) {
                AddNewClient(new_socket);
            } else {
                new_socket->close();
            }
            HandleConnection();
        });
    }


    void Server::HandleRead(socket_ptr s) {
        s->async_read_some(asio::buffer(clients_[s].buff, 1), [this, s](const asio::error_code &error, size_t bytes) {
            if (!error) {
                HandleUpdate(s);
            } else {
                clients_.erase(s);
                s->close();
            }
            HandleRead(s);
        });
    }

    void Server::AddNewClient(socket_ptr socket) {
        if (count_of_clients.load() == max_count_of_clients) return;
        clients_[socket].id = count_of_clients.fetch_add(1);
        clients_[socket].timer = std::make_shared<asio::steady_timer>(io_);
        HandleRead(std::move(socket));
    }

    void Server::DataUpdate(socket_ptr s) {
        std::lock_guard<std::mutex> m(mutex_);
        auto field = g_->UpdateField(clients_[s].buff[0], clients_[s].id);
        for (const auto &i: clients_) {
            i.first->write_some(asio::buffer(field));
        }
    }


} // joaquind