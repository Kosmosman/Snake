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

        void Start();
    };

} // joaquind

#endif //SNAKE_SERVER_H
