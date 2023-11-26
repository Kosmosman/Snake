//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <vector>
#include <iostream>
#include "abstract_object.h"
#include "one_dimensional_vector.h"

namespace joaquind {
    using size_t = unsigned long;

    constexpr size_t STANDARD_HEIGHT = 30;
    constexpr size_t STANDARD_WIDTH = 30;

    class Field : public AbstractObject {
    public:
        enum kFieldType {
            BORDER = '#', SNAKE = 'x', MEAL = 'o', FIELD = ' '
        };
        using coord_type = std::pair<size_t, size_t>;
        using field_type = std::vector<coord_type>;

        Field() : height_{STANDARD_HEIGHT}, width_{STANDARD_WIDTH} { Init(); };

        Field(size_t height, size_t width) : height_{height}, width_{width} { Init(); };

        explicit Field(coord_type field_size) : Field(field_size.second, field_size.first) { Init(); };

        const field_type &GetData() { return field_; };

        void Init() {
            field_.reserve((height_ + width_) * 2 - 4);

            for (int i = 0; i < width_; ++i) field_.emplace_back(0, i);
            for (int i = 0; i < width_; ++i) field_.emplace_back(height_ - 1, i);
            for (int i = 1; i < height_ - 1; ++i) field_.emplace_back(i, 0);
            for (int i = 1; i < height_ - 1; ++i) field_.emplace_back(i, width_ - 1);
        }

        void Resize(size_t new_height, size_t new_width) {
            field_.clear();
            height_ = new_height;
            width_ = new_width;
            Init();
        }

    private:
        size_t height_;
        size_t width_;
        field_type field_{}; // Y, X
    };

} // joaquind

#endif //SNAKE_FIELD_H
