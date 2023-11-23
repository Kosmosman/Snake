//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <unordered_map>
#include "configurations.h"

namespace joaquind {

    class Game {
    public:

        Game(Field *f, SnakeBuilder *s, Meal *m) : game_filed_(f), snakes_(s), meal_{m} {
            StartInit();
        };

        std::string UpdateField(char button, size_t id) {
            gamer_id_ = id;
            Move(button);
            if (!CheckCell()) {
                Reset();
            }
            return game_filed_->TransformToString();
        };

        void RemoveUser(size_t snake_id) {
            ClearSnakeCells();
            snakes_->RemoveSnake(snake_id);
        }

        void AddUser(size_t snake_id) {
            snakes_->AddSnake(game_filed_->GetSize(), snake_id);
        }

    private:

        void StartInit() {
            InitSnake();
            InitMeal();
        }

        void InitSnake() {
            for (auto &i: snakes_->GetSnake(gamer_id_).GetSnake())
                game_filed_->FillCell(i, Field::SNAKE);
        };

        void InitMeal() {
            std::pair<size_t, size_t> tmp{};
            while (game_filed_->GetCell(tmp) != Field::FIELD)
                tmp = (*meal_)(game_filed_->GetSize());
            game_filed_->FillCell(tmp, Field::MEAL);
        }

        void ClearSnakeCells() {
            auto snake{snakes_->GetSnake(gamer_id_)};
            for (auto i{++snake.GetSnake().begin()}; i != snake.GetSnake().end(); ++i)
                game_filed_->FillCell(*i, Field::kFieldType::FIELD);
            game_filed_->FillCell(snake.GetPrevTail(), Field::kFieldType::FIELD);
        }

        void Reset() {
            ClearSnakeCells();
            snakes_->GetSnake(gamer_id_).Init(game_filed_->GetSize());
        }

        void Move(char &button) {
            switch (button) {
                case 'w':
                    snakes_->GetSnake(gamer_id_).ChangeDirection(Snake::UP);
                    break;
                case 'd':
                    snakes_->GetSnake(gamer_id_).ChangeDirection(Snake::RIGHT);
                    break;
                case 's':
                    snakes_->GetSnake(gamer_id_).ChangeDirection(Snake::DOWN);
                    break;
                case 'a':
                    snakes_->GetSnake(gamer_id_).ChangeDirection(Snake::LEFT);
                    break;
                case 'p':
                    while (getchar() != 'p') continue;
                    break;
                default:
                    break;
            }
            snakes_->GetSnake(gamer_id_).Move();
        };

        bool CheckCell() {
            auto head{snakes_->GetSnake(gamer_id_).GetHead()};
            auto prev_tail{snakes_->GetSnake(gamer_id_).GetPrevTail()};
            if (game_filed_->GetCell(head) == Field::BORDER || game_filed_->GetCell(head) == Field::SNAKE) {
                return false;
            } else if (game_filed_->GetCell(head) == Field::MEAL) {
                snakes_->GetSnake(gamer_id_).Increase();
                game_filed_->FillCell(head, Field::SNAKE);
                InitMeal();
            } else {
                game_filed_->FillCell(head, Field::SNAKE);
                game_filed_->FillCell(prev_tail, Field::FIELD);
            }
            return true;
        };

        Field *game_filed_;
        SnakeBuilder *snakes_;
        Meal *meal_;
        size_t gamer_id_{};
    };

} // joaquind

#endif //SNAKE_GAME_H
