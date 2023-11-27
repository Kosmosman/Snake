//
// Created by Joaquina Daeron on 10/28/23.
//

#ifndef SNAKE_SERVER_H
#define SNAKE_SERVER_H

#include "asio.hpp"
#include "game.h"
#include <unordered_map>

namespace joaquind {

    class InputValidator {
    public:
        InputValidator()=default;
        bool Validate(char ch);
    private:
        char prev_char_{};
    };

    constexpr size_t max_count_of_clients = 2;
    constexpr size_t timer_iterator = 1000;

    struct ClientData {
        size_t id{};
        std::unique_ptr<asio::steady_timer> timer{};
        char buff[1]{};
    };

    class Server {
    public:
        explicit Server(Game *game) : g_{game} {};
        using size_t = unsigned long;
        using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;

        void Connect();

    private:
        void HandleRead(socket_ptr s);

        void HandleConnection();

        void AddNewClient(socket_ptr socket);

        void DataUpdate(socket_ptr s);

        void HandleTimeout(const asio::error_code &error, socket_ptr s);

        void HandleUpdate(Server::socket_ptr s);

        asio::io_context io_;
        asio::ip::tcp::endpoint ep_{asio::ip::tcp::v4(), 5000};
        asio::ip::tcp::acceptor acceptor_{io_, ep_};
        std::mutex mutex_{};

        Game *g_;
        std::atomic<size_t> count_of_clients_{};
        std::atomic<size_t> last_id_{};
        std::unordered_map<socket_ptr, ClientData> clients_; // socket, client_info
        InputValidator validator_{};
    };

} // joaquind

#endif //SNAKE_SERVER_H
