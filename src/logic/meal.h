//
// Created by Joaquina Daeron on 10/5/23.
//

#ifndef SNAKE_MEAL_H
#define SNAKE_MEAL_H

#include <random>

namespace joaquind {
    class Meal {
    public:
        using size_t = unsigned long;
        using coord_type = std::pair<size_t, size_t>;

        Meal() : mt_(rd_()), dist_(1, 1000) {};

        coord_type operator()(coord_type coord) {
            return {dist_(mt_) % coord.first, dist_(mt_) % coord.second};
        };
    private:
        std::random_device rd_{};
        std::mt19937 mt_;
        std::uniform_int_distribution<int> dist_;
    };

} // joaquind

#endif //SNAKE_MEAL_H
