//
// Created by Joaquina Daeron on 10/28/23.
//

#ifndef SNAKE_SERVER_H
#define SNAKE_SERVER_H

#include "asio.hpp"

namespace joaquind {

    class Server {
    public:
        using size_t = unsigned long;
        using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;

        void Connect();

    private:
        void Start(socket_ptr s);

        void NewConnection();

        asio::io_context io_;
        asio::ip::tcp::endpoint ep_{asio::ip::tcp::v4(), 5000};
        asio::ip::tcp::acceptor acceptor_{io_, ep_};
        char buff_[1]{};
    };

} // joaquind

#endif //SNAKE_SERVER_H
