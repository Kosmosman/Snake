//
// Created by Joaquina Daeron on 10/5/23.
//

#ifndef SNAKE_MEAL_H
#define SNAKE_MEAL_H

#include <random>
#include "abstract_object.h"

namespace joaquind {
    class Meal : public AbstractObject {
    public:
        using size_t = unsigned long;
        using coord_type = std::pair<size_t, size_t>;

        explicit Meal(coord_type field_size) : mt_(rd_()), dist_(1, 1000), position_(1) { Init(field_size); };

        void Init(coord_type coord) {
            position_[0] = {dist_(mt_) % (coord.first - 1) + 1, dist_(mt_) % (coord.second - 1) + 1};
        };

        [[nodiscard]] const std::vector<coord_type>& GetData() const { return position_; };

    private:
        std::vector<coord_type> position_{};
        std::random_device rd_{};
        std::mt19937 mt_;
        std::uniform_int_distribution<int> dist_;
    };

} // joaquind

#endif //SNAKE_MEAL_H
