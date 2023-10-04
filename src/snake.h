//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <list>
#include <vector>

#include "configurates.h"

namespace joaquind {

    class snake {
    public:
        using size_t = unsigned long;
        snake(const field& f) {
            for (int i = 0; i < 3; ++i) snake_body_.emplace_front(field_height / 2 - i, field_width / 2);
        };
        void move(int&& vertical, int&& horizontal) {

        }
        void reset() {};
    private:
        std::list<> snake_body_;
    };

} // joaquind

#endif //SNAKE_SNAKE_H
