//
// Created by Joaquina Daeron on 10/28/23.
//

#include "client.h"
#include <termios.h>
#include <iostream>

namespace joaquind {
    void Client::Connect() {
        TurnOffBufferingInput();
        s_.async_connect(ep_, [this](const asio::error_code &e) { if (!e) Session(); });
        io_.run();
    }

    void Client::TurnOffBufferingInput() {
        struct termios settings{};
        tcgetattr(STDIN_FILENO, &settings);
        settings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &settings);
    }

    void Client::Session() {
        ReadFromConsole();
        ReadFromSocket();
    }

    void Client::WriteToSocket() {
        s_.async_write_some(asio::buffer(symbol_, 1),
                            [this](const asio::error_code &e, std::size_t) { if (!e) ReadFromConsole(); });
    }

    void Client::ReadFromConsole() {
        input_.async_read_some(asio::buffer(symbol_, 1),
                               [this](const asio::error_code &e, std::size_t) { if (!e) WriteToSocket(); });
    }

    void Client::ReadFromSocket() {
        s_.async_read_some(asio::buffer(buffer_),
                           [this](const asio::error_code &e, std::size_t bytes) {
                               if (!e && bytes)
                                   PrintField();
                               else
                                   ReadFromSocket();
                           });
    }

    void Client::PrintField() {
        for (int i{}; buffer_[i]; ++i)
            std::cout << buffer_[i];
        ReadFromSocket();
    }


} // joaquind
