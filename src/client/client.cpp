//
// Created by Joaquina Daeron on 10/28/23.
//

#include "client.h"
#include "interpreter.h"
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
        ReadFromSocket();
    }

    void Client::WriteToSocket() {
        s_.write_some(asio::buffer(symbol_, 1));
    }

    void Client::ReadFromSocket() {
        s_.async_read_some(asio::buffer(buffer_),
                           [this](const asio::error_code &e, std::size_t bytes) {
                               if (!e && bytes) {
                                   buffer_.resize(bytes);
                                   PrintField();
                                   NotifyObservers();
                               } else {
                                   ReadFromSocket();
                               }
                           });
    }

    void Client::PrintField() {
        for (int i{}; buffer_[i]; ++i)
            std::cout << buffer_[i];
        ReadFromSocket();
    }

    void Client::AddObserver(Observer *obs) {
        observers_.push_back(obs);
    }

    void Client::RemoveObserver(Observer *obs) {
        observers_.remove(obs);
    }

    void Client::NotifyObservers() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto data = Interpreter<std::vector<char>>::TransformToCoordType(buffer_);
        for (auto &i: observers_)
            i->OnUpdate(data);
    }

    void Client::OnKeyPressed(char ch) {
        std::cout << "Was pressed " << ch << '\n';
        symbol_[0] = ch;
        WriteToSocket();
    }


} // joaquind
