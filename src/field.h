//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <vector>
#include "configurates.h"

namespace joaquind {
    template <size_t H = 30, size_t W = 50>
    class field {
    public:
        using size_t = unsigned long;
        using field_type = std::vector<std::vector<char>>;

        field() : field_(H, std::vector<char>(W, ' ')) {
            for (int i = 0; i < W; ++i) field_[0][i] = field_[H - 1][i] = '#';
            for (int i = 1; i < H - 1; ++i) field_[i][0] = field_[i][W - 1] = '#';
        };
        field_type& GetField() {return field_;}

    private:
        size_t height_{H};
        size_t width_{W};
        field_type field_;
    };

} // joaquind

#endif //SNAKE_FIELD_H
