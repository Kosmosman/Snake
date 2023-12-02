//
// Created by Joaquina Daeron on 11/30/23.
//

#ifndef SNAKE_INTERPRETER_H
#define SNAKE_INTERPRETER_H

#include <string>
#include <vector>
#include "types.h"

namespace joaquind {
    template<typename T>
    concept Iterable = requires(T t) {
        begin(t);
        end(t);
    };

    template <Iterable Container>
    class Interpreter {
    public:
        static std::vector<FieldCell> TransformToCoordType(Container &s) {
            std::vector<FieldCell> field(s.size() * 2);
            size_t x{1}, y{1};
            size_t counter{};
            for (auto &i: s) {
                if (i == '\n') {
                    ++y;
                    x = 1;
                } else {
                    field[counter++] = {x++, y, ChooseType(i)};
                }
            }
            field.resize(counter);
            return field;
        }

    private:
        static CellType ChooseType(char ch) {
            switch (ch) {
                case '#':
                    return CellType::kBorder;
                case ' ':
                    return CellType::kField;
                case 'x':
                    return CellType::kSnake;
                case 'o':
                    return CellType::kMeal;
                default:
                    return CellType::kNone;
            }
        }
    };
}


#endif //SNAKE_INTERPRETER_H
