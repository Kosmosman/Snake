//
// Created by Joaquina Daeron on 10/28/23.
//

#ifndef SNAKE_CLIENT_H
#define SNAKE_CLIENT_H

#include "asio.hpp"
#include "interpreter.h"
#include "observer.h"
#include <iostream>
#include <sys/socket.h>
#include <list>
#include <mutex>

namespace joaquind {

    class Client {
    public:

        Client() : buffer_(1024) {}

        void Connect();

        void AddObserver(Observer* obs);

        void RemoveObserver(Observer *obs);

        void NotifyObservers();

    private:
        void TurnOffBufferingInput();

        void Session();

        void WriteToSocket();

        void ReadFromConsole();

        void ReadFromSocket();

        void PrintField();

        void TranslateToMainWindow();

        asio::io_context io_{};
        asio::ip::tcp::endpoint ep_{asio::ip::address::from_string("127.0.0.1"), 5000};
        asio::ip::tcp::socket s_{io_};
        asio::posix::stream_descriptor input_{io_, ::dup(STDIN_FILENO)};
        std::mutex mutex_{};
        char symbol_[1]{};
        std::vector<char> buffer_;
        std::list<Observer*> observers_{};
    };

} // joaquind

#endif //SNAKE_CLIENT_H
