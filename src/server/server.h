//
// Created by Joaquina Daeron on 10/28/23.
//

#ifndef SNAKE_SERVER_H
#define SNAKE_SERVER_H

#include "asio.hpp"
#include "game.h"
#include <unordered_map>

namespace joaquind {
    constexpr size_t max_count_of_clients = 2;

    class Server {
    public:
        explicit Server(Game *game) : clients_(2), g_{game}, t_(io_, std::chrono::seconds(2)) {};
        using size_t = unsigned long;
        using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;

        void Connect();

    private:
        void Start(socket_ptr s);

        void NewConnection();

        void AddNewClient(socket_ptr socket);

        void DataUpdate(size_t id);

        asio::io_context io_;
        asio::ip::tcp::endpoint ep_{asio::ip::tcp::v4(), 5000};
        asio::ip::tcp::acceptor acceptor_{io_, ep_};
        char buff_[2]{};
        std::atomic<size_t> count_of_clients{};
        std::unordered_map<socket_ptr, size_t> clients_; // socket, id
        Game *g_;
        std::mutex mutex_{};
        asio::system_timer t_;
    };

} // joaquind

#endif //SNAKE_SERVER_H
