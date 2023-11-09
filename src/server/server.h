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

    struct ClientData {
        size_t id{};
        std::shared_ptr<asio::steady_timer> timer{};
        char buff[1]{};
    };

    class Server {
    public:
        explicit Server(Game *game) : g_{game} {};
        using size_t = unsigned long;
        using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;

        void Connect();

    private:
        void Start(socket_ptr s);

        void NewConnection();

        void AddNewClient(socket_ptr socket);

        void DataUpdate(socket_ptr s);

        void HandleTimeout(const asio::error_code &error, socket_ptr s);

        void UpdateHandler(socket_ptr s);

        asio::io_context io_;
        asio::ip::tcp::endpoint ep_{asio::ip::tcp::v4(), 5000};
        asio::ip::tcp::acceptor acceptor_{io_, ep_};
        std::mutex mutex_{};

        Game *g_;
        std::atomic<size_t> count_of_clients{};
        std::unordered_map<socket_ptr, ClientData> clients_; // socket, client_info
    };

} // joaquind

#endif //SNAKE_SERVER_H
