//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <unordered_map>
#include <utility>
#include "configurations.h"
#include "transformator.h"

namespace joaquind {

    class Game {
    public:

        Game(ObjectManager *manager, coord_type field_size) : manager_{manager}, field_size_{std::move(field_size)},
                                                              transformator_(field_size) {
            StartInit();
        };

        std::string UpdateField(char button, size_t id) {
            gamer_id_ = id;
            Move(button);
            CheckCell();
            transformator_.TransformFieldToString(manager_->Get<Field>());
            transformator_.TransformSnakeToString(manager_->Get<Snake>());
            transformator_.TransformMealToString(manager_->Get<Meal>());
            return transformator_.GetData();
        };

        void RemoveUser(size_t snake_id) {
            manager_->Remove<Snake>(snake_id);
        }

        void AddUser() {
            manager_->Create<Snake>(field_size_);
        }

    private:

        void StartInit() {
            manager_->Create<Field>(field_size_);
            manager_->Create<Meal>(field_size_);
        }

        void InitSnake() {
            manager_->Get<Snake>()[gamer_id_]->Init(
                    {field_size_.first / ((gamer_id_ + 2) % field_size_.first),
                     field_size_.second / ((gamer_id_ + 2) % field_size_.second)});
        };

        void InitMeal() {
            for (auto &i: manager_->Get<Meal>()) {
                i.second->Init(field_size_);
                auto meal_coord{i.second->GetData()};
                while (manager_->Get<Field>()[0]->GetCell(meal_coord[0]) != Field::FIELD) {
                    i.second->Init(field_size_);
                    meal_coord = i.second->GetData();
                }
            }
        }

        void Reset() {
            InitSnake();
        }

        void Move(char &button) {
            auto snake = manager_->Get<Snake>()[gamer_id_];
            switch (button) {
                case 'w':
                    snake->ChangeDirection(Snake::UP);
                    break;
                case 'd':
                    snake->ChangeDirection(Snake::RIGHT);
                    break;
                case 's':
                    snake->ChangeDirection(Snake::DOWN);
                    break;
                case 'a':
                    snake->ChangeDirection(Snake::LEFT);
                    break;
                case 'p':
                    while (getchar() != 'p') continue;
                    break;
                default:
                    break;
            }
            snake->Move();
        };

        void CheckCell() {
            auto head_cell{manager_->Get<Snake>()[gamer_id_]->GetHead()};
            auto head_cell_type{manager_->Get<Field>()[0]->GetCell(head_cell)};
            if (head_cell_type == Field::BORDER || CheckSnakeIntersect(head_cell)) {
                Reset();
            } else if (CheckMealIntersect(head_cell)) {
                manager_->Get<Snake>()[gamer_id_]->Increase();
                InitMeal();
            }
        };

        bool CheckSnakeIntersect(coord_type head_cell) {
            for (auto &[id, snake]: manager_->Get<Snake>()) {
                if (id != gamer_id_) {
                    for (auto &cell: snake->GetData()) {
                        if (head_cell == cell)
                            return true;
                    }
                }
            }
            auto snake{manager_->Get<Snake>()[gamer_id_]->GetData()};
            for (auto i{++snake.begin()}; i != snake.end(); ++i) {
                if (head_cell == *i)
                    return true;
            }
            return false;
        }

        bool CheckMealIntersect(coord_type head_cell) {
            for (auto &[id, meal]: manager_->Get<Meal>()) {
                for (auto &cell: meal->GetData()) {
                    if (head_cell == cell)
                        return true;
                }
            }
            return false;
        }

        coord_type field_size_{};
        ObjectManager *manager_{};
        Transformator transformator_;
        size_t gamer_id_{};
    };

} // joaquind

#endif //SNAKE_GAME_H
