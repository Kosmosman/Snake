//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <vector>
#include "configurates.h"
#include <iostream>

namespace joaquind {
    using size_t = unsigned long;

    constexpr size_t STANDARD_HEIGHT = 30;
    constexpr size_t STANDARD_WIDTH = 30;

    class field {
    public:
        enum kFieldType {
            BORDER = '#', SNAKE = 'x', MEAL = 'o', FIELD = ' '
        };
        using coord_type = std::pair<::size_t, ::size_t>;
        using field_type = std::vector<std::vector<char>>;

        field(size_t height, size_t width) : height_{height}, width_{width},
                                             field_(height, std::vector<char>(width, ' ')) { Init(); };

        field() : field_(STANDARD_HEIGHT, std::vector<char>(STANDARD_WIDTH, ' ')), height_{STANDARD_HEIGHT},
                  width_{STANDARD_WIDTH} { Init(); };

        void FillCell(coord_type coord, kFieldType type) { field_[coord.first][coord.second] = type; };

        kFieldType GetCell(coord_type coord) { return static_cast<kFieldType>(field_[coord.first][coord.second]); };

        coord_type GetSize() { return {height_, width_}; };

        void PrintField() {
            for (const auto &i: field_) {
                for (const char &j: i) {
                    std::cout << j;
                }
                std::cout << '\n';
            }
        }

        void Init() {
            for (int i = 0; i < width_; ++i) field_[0][i] = field_[height_ - 1][i] = BORDER;
            for (int i = 1; i < height_ - 1; ++i) field_[i][0] = field_[i][width_ - 1] = BORDER;
        }

        void Clear() {
            for (int i = 1; i < height_ - 1; ++i)
                for (int j = 1; j < width_ - 1; ++j)
                    field_[i][j] = FIELD;
        }

    private:
        field_type field_;
        size_t height_;
        size_t width_;
    };

} // joaquind

#endif //SNAKE_FIELD_H
