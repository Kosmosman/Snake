//
// Created by Joaquina Daeron on 10/4/23.
//

#ifndef SNAKE_FIELD_H
#define SNAKE_FIELD_H

#include <vector>
#include <iostream>
#include "abstract_object.h"

namespace joaquind {
    using size_t = unsigned long;

    constexpr size_t STANDARD_HEIGHT = 30;
    constexpr size_t STANDARD_WIDTH = 30;
    constexpr size_t MAX_SIZE = 100;

    class Field : public AbstractObject {
    public:
        enum kFieldType {
            BORDER = '#', SNAKE = 'x', MEAL = 'o', FIELD = ' '
        };
        using coord_type = std::pair<size_t, size_t>;
        using field_type = std::vector<std::vector<char>>;

        Field(size_t height, size_t width) : height_{CheckCorrectFieldSize(height, width) ? height : STANDARD_HEIGHT},
                                             width_{CheckCorrectFieldSize(height, width) ? width : STANDARD_WIDTH},
                                             field_{height_, std::vector<char>(width_, ' ')} {
            Init();
        };

        explicit Field(coord_type field_size) : Field(field_size.second, field_size.first) {}

        Field() : height_{STANDARD_HEIGHT}, width_{STANDARD_WIDTH},
                  field_{height_, std::vector<char>(width_, ' ')} { Init(); };

        kFieldType GetCell(coord_type coord) { return static_cast<kFieldType>(field_[coord.first][coord.second]); };

        coord_type GetSize() { return {height_, width_}; };

        const field_type& GetData() { return field_; };

        void Init() {
            if (height_ <= 0 || width_ <= 0) {
                height_ = STANDARD_HEIGHT;
                width_ = STANDARD_WIDTH;
            }
            for (int i = 0; i < width_; ++i) field_[0][i] = field_[height_ - 1][i] = BORDER;
            for (int i = 0; i < height_; ++i) field_[i][0] = field_[i][width_ - 1] = BORDER;
        }

        void Clear() {
            for (int i = 1; i < height_ - 1; ++i)
                for (int j = 1; j < width_ - 1; ++j)
                    field_[i][j] = FIELD;
        }

        std::string TransformToString() {
            std::string string_view;
            string_view.reserve(height_ * width_ + height_);
            for (auto &i: field_) {
                string_view += std::string{i.begin(), i.end()} + '\n';
            }
            return std::move(string_view);
        }



    private:
        size_t height_;
        size_t width_;
        field_type field_;

        bool CheckCorrectFieldSize(size_t h, size_t w) { return h * w > 0 && h <= MAX_SIZE && w <= MAX_SIZE; };
    };

} // joaquind

#endif //SNAKE_FIELD_H
