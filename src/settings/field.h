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

    template <size_t H = 30, size_t W = 50>
    class field {
    public:
        enum kFieldType{BORDER = '#', SNAKE = 'x', MEAL = 'o', FIELD = ' '};
        using coord_type = std::pair<::size_t, ::size_t>;
        using field_type = std::vector<std::vector<char>>;

        field() : field_(H, std::vector<char>(W, ' ')) {Init();};

        void FillCell(coord_type coord, kFieldType type) {field_[coord.first][coord.second] = type;};
        kFieldType GetCell(coord_type coord) {return static_cast<kFieldType>(field_[coord.first][coord.second]);};
        coord_type GetSize() {return {H, W};};

        void PrintField() {
            for (const auto &i: field_) {
                for (const char& j: i) {
                    std::cout << j;
                }
                std::cout << '\n';
            }
        }
        void Init() {
            for (int i = 0; i < W; ++i) field_[0][i] = field_[H - 1][i] = BORDER;
            for (int i = 1; i < H - 1; ++i) field_[i][0] = field_[i][W - 1] = BORDER;
        }
        void Clear() {
            for (int i = 1; i < H - 1; ++i)
                for (int j = 1; j < W - 1; ++j)
                    field_[i][j] = FIELD;
        }
    private:
        field_type field_;
    };

} // joaquind

#endif //SNAKE_FIELD_H
