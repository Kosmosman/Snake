//
// Created by Joaquina Daeron on 11/24/23.
//

#ifndef SNAKE_OBJECT_BUILDER_H
#define SNAKE_OBJECT_BUILDER_H

#include <memory>

namespace joaquind {

    using size_t = unsigned long;
    using coord_type = std::pair<size_t, size_t>;

    template <typename T>
    class ObjectBuilder {
    public:
        std::shared_ptr<T> Create(coord_type field_size) {
            return std::make_shared<T>(field_size);
        }
    };

} // joaquind

#endif //SNAKE_OBJECT_BUILDER_H
