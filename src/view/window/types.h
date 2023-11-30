//
// Created by Joaquina Daeron on 11/30/23.
//

#ifndef SNAKE_TYPES_H
#define SNAKE_TYPES_H

namespace joaquind {

    using size_t = unsigned long;

    enum class CellType {
        kNone, kField, kBorder, kSnake, kMeal
    };

    struct FieldCell {
        size_t x;
        size_t y;
        CellType type;
    };

}

#endif //SNAKE_TYPES_H
