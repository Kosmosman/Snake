//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>
#include <list>
#include "abstract_object.h"

namespace joaquind {

    class Snake : public AbstractObject {
    public:
        using size_t = unsigned long;
        using coord_type = std::pair<size_t, size_t>;
        using snake_type = std::list<coord_type>;

        enum kDirection {
            UP, RIGHT, DOWN, LEFT
        };

        Snake() = default;

        explicit Snake(coord_type coord) : snake_size_{start_snake_size_},
                                           snake_body_{coord.first * coord.second} { Init(coord); };

        [[nodiscard]] const coord_type &GetHead() const { return snake_body_.front(); };

        [[nodiscard]] const snake_type &GetData() const { return snake_body_; };

        void Init(coord_type coord) {
            snake_size_ = start_snake_size_;
            snake_body_.resize(start_snake_size_);
            prev_tail = {};
            direction_ = RIGHT;
            auto it{snake_body_.begin()};
            for (auto i = 0; i < snake_size_; ++i)
                *(it++) = {coord.first / 2, coord.second / 2 - i};
        };

        void SetDirectionAndMove(char button) {
            switch (button) {
                case 'w':
                    if (direction_ != Snake::DOWN) ChangeDirection(Snake::UP);
                    break;
                case 'd':
                    if (direction_ != Snake::LEFT) ChangeDirection(Snake::RIGHT);
                    break;
                case 's':
                    if (direction_ != Snake::UP) ChangeDirection(Snake::DOWN);
                    break;
                case 'a':
                    if (direction_ != Snake::RIGHT) ChangeDirection(Snake::LEFT);
                    break;
                default:
                    break;
            }
            Move();
        }

        void ChangeDirection(kDirection direction) {
            direction_ = direction;
        };

        void Increase() {
            snake_body_.emplace_back(prev_tail);
            ++snake_size_;
        };

    private:
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

        void MakeMove(int diff_v, int diff_h) {
            auto tmp = std::make_pair(snake_body_.front().first + diff_v, snake_body_.front().second + diff_h);
            snake_body_.push_front(std::move(tmp));
            prev_tail = snake_body_.back();
            snake_body_.pop_back();
        };

        static constexpr size_t start_snake_size_{3};
        size_t snake_size_{};
        coord_type prev_tail{};
        snake_type snake_body_;  // Y, X
        size_t direction_{RIGHT};
    };

} // joaquind

#endif //SNAKE_SNAKE_H
