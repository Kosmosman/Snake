//
// Created by Joaquina Daeron on 11/17/23.
//

#ifndef SNAKE_SNAKE_BUILDER_H
#define SNAKE_SNAKE_BUILDER_H

#include <unordered_map>
#include "snake.h"

namespace joaquind {

    using size_t = unsigned long;
    using coord_type = std::pair<size_t, size_t>;

    class SnakeBuilder {
    public:
        SnakeBuilder() = default;
        void AddSnake(coord_type field_size, size_t snake_id) {
            snakes_[snake_id] = Snake(field_size);
            snakes_[snake_id].Init({field_size.first / (snake_id + 1), field_size.second});
        }
        void RemoveSnake(size_t snake_id) {
            snakes_.erase(snake_id);
        }
        Snake& GetSnake(size_t snake_id) {
            return snakes_[snake_id];
        }
    private:
        std::unordered_map<size_t, Snake> snakes_{};
    };

} // joaquind

#endif //SNAKE_SNAKE_BUILDER_H
