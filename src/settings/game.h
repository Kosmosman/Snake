//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "configurates.h"
#include <termios.h>
#include <unistd.h>

namespace joaquind {

//    template <typename F, typename S>
    class game {
    public:
        using coord_type = std::pair<::size_t, ::size_t>;

        game(field<>& f, snake& s) : game_filed_(f), snake_(s) {};

        void start() {
            InitInput();
            InitSnake();
            while (true) {
                game_filed_.PrintField();
                char button{ReadButton()};
                auto tail{snake_.GetTail()};
                Move(button);
                if (!CheckCell(tail)) Reset();
            }
        };

    private:
        void InitInput() {
            struct termios old_settings, new_settings;
            tcgetattr(STDIN_FILENO, &old_settings);
            new_settings = old_settings;
            new_settings.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        };

        void InitSnake() {
            for (auto &i: snake_.GetSnake())
                game_filed_.FillCell(i, field<>::SNAKE);
        };

        void Reset() {
            game_filed_.Clear();
            game_filed_.Init();
            snake_.Init(game_filed_.GetSize());
            InitSnake();
        }

        char ReadButton() {
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(STDIN_FILENO, &readfds);

            struct timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 100000;

            int ready = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout);
            char input{};
            if (ready > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
                input = static_cast<char>(getchar());
            }
            return input;
        };

        void Move(char& button) {
            switch (button) {
                case 'w':
                    snake_.ChangeDirection(snake::UP);
                    break;
                case 'd':
                    snake_.ChangeDirection(snake::RIGHT);
                    break;
                case 's':
                    snake_.ChangeDirection(snake::DOWN);
                    break;
                case 'a':
                    snake_.ChangeDirection(snake::LEFT);
                    break;
                default:
                    break;
            }
            snake_.Move();
        };

        bool CheckCell(coord_type& deleted) {
            auto head{snake_.GetHead()};
            if (game_filed_.GetCell(head) == field<>::BORDER || game_filed_.GetCell(head) == field<>::SNAKE) {
                return false;
            } else if (game_filed_.GetCell(head) == field<>::MEAL) {
                snake_.Increase(deleted);
            } else {
                game_filed_.FillCell(head, field<>::SNAKE);
                game_filed_.FillCell(deleted, field<>::FIELD);
            }
            return true;
        };

        field<> game_filed_;
        snake snake_;
    };

} // joaquind

#endif //SNAKE_GAME_H
