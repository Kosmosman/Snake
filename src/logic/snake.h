//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>

namespace joaquind {

    class Snake {
    public:
        using size_t = unsigned long;
        using coord_type = std::pair<size_t, size_t>;
        using snake_type = std::vector<coord_type>;
        enum kDirection {
            UP, RIGHT, DOWN, LEFT
        };

        explicit Snake(coord_type coord) : snake_size_{start_snake_size_},
                                           snake_body_(coord.first * coord.second) { Init(coord); };

        const coord_type &GetHead() { return snake_body_[0]; };

        const coord_type &GetTail() { return snake_body_[snake_size_ - 1]; };

        const snake_type &GetSnake() { return snake_body_; };

        void ChangeDirection(kDirection direction) { direction_ = direction; };

        void Init(coord_type coord) {
            snake_size_ = start_snake_size_;
            direction_ = RIGHT;
            for (auto i = 0; i < snake_size_; ++i)
                snake_body_[i] = {coord.first / 2, coord.second / 2 - i};
        };

        void Move() {
            switch (direction_) {
                case RIGHT:
                    MakeMove(0, 1);
                    break;
                case LEFT:
                    MakeMove(0, -1);
                    break;
                case UP:
                    MakeMove(-1, 0);
                    break;
                case DOWN:
                    MakeMove(1, 0);
                    break;
            }
        };

        void Increase(coord_type coord) {
            snake_body_[snake_size_++] = coord;
        };

    private:
        coord_type MakeMove(int diff_v, int diff_h) {
            auto tmp = std::make_pair(snake_body_[0].first + diff_v, snake_body_[0].second + diff_h);
            for (int i = 0; i < snake_size_; ++i) {
                std::swap(tmp, snake_body_[i]);
            }
            return tmp;
        };

        static constexpr size_t start_snake_size_{3};
        size_t snake_size_;
        snake_type snake_body_;  // Y, X
        size_t direction_{RIGHT};
    };

} // joaquind

#endif //SNAKE_SNAKE_H
