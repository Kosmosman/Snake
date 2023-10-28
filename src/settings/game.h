//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "configurates.h"
#include <termios.h>
#include <unistd.h>

namespace joaquind {

    class Game {
    public:
        using coord_type = std::pair<size_t, size_t>;

        Game(Field *f, Snake *s, Meal* m) : game_filed_(f), snake_(s), meal_{m} {};

        void start() {
            StartInit();
            while (!ReadButton());
            while (true) {
                game_filed_->PrintField();
                char button{ReadButton()};
                auto tail{snake_->GetTail()};
                Move(button);
                if (!CheckCell(tail)) {
                    Reset();
                    while (!ReadButton());
                }
            }
        };

    private:

        void StartInit() {
            InitInput();
            InitSnake();
            InitMeal();
        }

        void InitInput() {
            struct termios old_settings{}, new_settings{};
            tcgetattr(STDIN_FILENO, &old_settings);
            new_settings = old_settings;
            new_settings.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
        };

        void InitSnake() {
            for (auto &i: snake_->GetSnake())
                game_filed_->FillCell(i, Field::SNAKE);
        };

        void InitMeal() {
            coord_type tmp{0, 0};
            while (game_filed_->GetCell(tmp) != Field::FIELD)
                tmp = (*meal_)(game_filed_->GetSize());
            game_filed_->FillCell(tmp, Field::MEAL);
        }

        void Reset() {
            game_filed_->Clear();
            game_filed_->Init();
            snake_->Init(game_filed_->GetSize());
            InitMeal();
        }

        char ReadButton() {
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(STDIN_FILENO, &readfds);

            struct timeval timeout{};
            timeout.tv_sec = 0;
            timeout.tv_usec = 100000;

            int ready = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout);
            char input{};
            if (ready > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
                input = static_cast<char>(getchar());
            }
            return input;
        };

        void Move(char &button) {
            switch (button) {
                case 'w':
                    snake_->ChangeDirection(Snake::UP);
                    break;
                case 'd':
                    snake_->ChangeDirection(Snake::RIGHT);
                    break;
                case 's':
                    snake_->ChangeDirection(Snake::DOWN);
                    break;
                case 'a':
                    snake_->ChangeDirection(Snake::LEFT);
                    break;
                case 'p':
                    while (getchar() != 'p') continue;
                    break;
                default:
                    break;
            }
            snake_->Move();
        };

        bool CheckCell(coord_type &deleted) {
            auto head{snake_->GetHead()};
            if (game_filed_->GetCell(head) == Field::BORDER || game_filed_->GetCell(head) == Field::SNAKE) {
                return false;
            } else if (game_filed_->GetCell(head) == Field::MEAL) {
                snake_->Increase(deleted);
                InitMeal();
            } else {
                game_filed_->FillCell(head, Field::SNAKE);
                game_filed_->FillCell(deleted, Field::FIELD);
            }
            return true;
        };

        Field* game_filed_;
        Snake* snake_;
        Meal* meal_;
    };

} // joaquind

#endif //SNAKE_GAME_H
