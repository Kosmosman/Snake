//
// Created by Joaquina Daeron on 11/25/23.
//

#ifndef SNAKE_VALIDATOR_H
#define SNAKE_VALIDATOR_H

#include <components/object_manager.h>

namespace joaquind {

    class Validator {
    public:
        bool CheckMealValidate(ObjectManager *om, size_t meal_id) {

        }

        bool CheckSnakeValidate(ObjectManager *om, size_t snake_id) {
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

        bool CheckIntersersectSnakeAndMeal(ObjectManager *om, size_t snake_id) {

        }

    };

} // joaquind

#endif //SNAKE_VALIDATOR_H
