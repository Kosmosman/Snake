//
// Created by Joaquina Daeron on 10/28/23.
//

#include "client.h"
#include <termios.h>

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
        auto str = std::make_shared<std::string>();
        s_.async_read_some(asio::buffer(*str),
                           [this, str](const asio::error_code &e, std::size_t bytes) {
                               if (!e && bytes)
                                   PrintField(str);
                           });
    }

    void Client::PrintField(const std::shared_ptr<std::string> &s_ptr) {
        std::cout << *s_ptr << '\n';
        ReadFromSocket();
    }


} // joaquind