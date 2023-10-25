//
// Created by Joaquina Daeron on 10/7/23.
//

#ifndef SNAKE_SERVER_H
#define SNAKE_SERVER_H

#include "asio.hpp"

namespace joaquind {

    class Server {
    public:
    private:
        asio::io_context io_;
        asio::ip::tcp::endpoint ep_;
        asio::ip::tcp::acceptor ac_;
    };

} // joaquind

#endif //SNAKE_SERVER_H
