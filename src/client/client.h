//
// Created by Joaquina Daeron on 10/28/23.
//

#ifndef SNAKE_CLIENT_H
#define SNAKE_CLIENT_H

#include "asio.hpp"
#include <iostream>
#include <sys/socket.h>

namespace joaquind {

    class Client {
    public:
        void Connect();

    private:
        void TurnOffBufferingInput();

        void Session();

        void WriteToSocket();

        void ReadFromConsole();

        void ReadFromSocket();

        void PrintField();

        asio::io_context io_{};
        asio::ip::tcp::endpoint ep_{asio::ip::address::from_string("127.0.0.1"), 5000};
        asio::ip::tcp::socket s_{io_};
        asio::posix::stream_descriptor input_{io_, ::dup(STDIN_FILENO)};
        char symbol_[1]{};
        char buffer_[1024]{};
    };

} // joaquind

#endif //SNAKE_CLIENT_H
