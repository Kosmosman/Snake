//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <unordered_map>
#include <utility>
#include "configurations.h"
#include "transformator.h"
#include "validator.h"

namespace joaquind {

    class Game {
    public:

        Game(ObjectManager *manager, coord_type field_size) : manager_{manager}, field_size_{std::move(field_size)},
                                                              transformator_(field_size) {
            manager_->Create<Field>(field_size_);
            manager_->Create<Meal>(field_size_);
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

        void InitSnake() {
            manager_->Get<Snake>()[gamer_id_]->Init(
                    {field_size_.first / ((gamer_id_ + 2) % field_size_.first),
                     field_size_.second / ((gamer_id_ + 2) % field_size_.second)});
        };

        void InitMeal(int meal_id) {
            auto meal = manager_->Get<Meal>()[meal_id];
            meal->Init(field_size_);
            while (Validator::CheckMealValidate(manager_, meal_id))
                meal->Init(field_size_);
        }

        void Reset() {
            InitSnake();
        }

        void Move(char &button) {
            auto snake = manager_->Get<Snake>()[gamer_id_];
            snake->SetDirectionAndMove(button);
        };

        void CheckCell() {
            if (Validator::CheckSnakeValidate(manager_, gamer_id_)) {
                Reset();
            }
            auto meal_id = Validator::CheckIntersectSnakeAndMeal(manager_, gamer_id_);
            if (meal_id >= 0) {
                manager_->Get<Snake>()[gamer_id_]->Increase();
                InitMeal(meal_id);
            }
        };

        coord_type field_size_{};
        ObjectManager *manager_{};
        Transformator transformator_;
        size_t gamer_id_{};
    };

} // joaquind

#endif //SNAKE_GAME_H
