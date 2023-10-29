//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "configurations.h"
#include <termios.h>
#include <unistd.h>

namespace joaquind {

    class Game {
    public:
        using coord_type = std::pair<size_t, size_t>;

        Game(Field *f, Snake *s, Meal* m) : game_filed_(f), snake_(s), meal_{m} {
            StartInit();
        };

        std::string UpdateField(char button) {
            auto tail{snake_->GetTail()};
            Move(button);
            if (!CheckCell(tail)) {
                Reset();
            }
            return game_filed_->TransformToString();
        };

    private:

        void StartInit() {
            InitSnake();
            InitMeal();
        }

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
