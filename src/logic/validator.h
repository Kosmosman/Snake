//
// Created by Joaquina Daeron on 11/25/23.
//

#ifndef SNAKE_VALIDATOR_H
#define SNAKE_VALIDATOR_H

#include "components/object_manager.h"

namespace joaquind {

    class Validator {
    public:
        static bool CheckMealValidate(ObjectManager *om, size_t meal_id) {
            auto meal_pos = om->Get<Meal>()[meal_id]->GetData()[0];
            for (auto &[_, snake]: om->Get<Snake>()) {
                for (auto &snake_cell: snake->GetData()) {
                    if (meal_pos == snake_cell) {
                        return true;
                    }
                }
            }

            for (auto &[meal_local_id, meal]: om->Get<Meal>()) {
                if (meal_id != meal_local_id) {
                    for (auto &meal_cell: meal->GetData()) {
                        if (meal_pos == meal_cell) {
                            return true;
                        }
                    }
                }
            }

            for (auto &[_, field]: om->Get<Field>()) {
                for (auto &field_cell: field->GetData()) {
                    if (meal_pos == field_cell) {
                        return true;
                    }
                }
            }

            return false;
        }

        static bool CheckSnakeValidate(ObjectManager *om, size_t snake_id) {
            auto head_cell = om->Get<Snake>()[snake_id]->GetHead();
            // Check intersect snake and border
            for (auto &[id, field]: om->Get<Field>()) {
                for (auto &cell: field->GetData()) {
                    if (head_cell == cell)
                        return true;
                }
            }

            // Check intersect snake and other snake
            for (auto &[id, snake]: om->Get<Snake>()) {
                if (id != snake_id) {
                    for (auto &cell: snake->GetData()) {
                        if (head_cell == cell)
                            return true;
                    }
                }
            }

            // Check snake's self-intersect
            auto snake{om->Get<Snake>()[snake_id]->GetData()};
            for (auto i{++snake.begin()}; i != snake.end(); ++i) {
                if (head_cell == *i)
                    return true;
            }
            return false;
        }

        static int CheckIntersectSnakeAndMeal(ObjectManager *om, size_t snake_id) {
            auto head_cell = om->Get<Snake>()[snake_id]->GetHead();
            for (auto &[meal_id, meal]: om->Get<Meal>()) {
                for (auto &meal_pos: meal->GetData()) {
                    if (head_cell == meal_pos)
                        return static_cast<int>(meal_id);
                }
            }
            return -1;
        }

    };

} // joaquind

#endif //SNAKE_VALIDATOR_H
