//
// Created by Joaquina Daeron on 11/25/23.
//

#ifndef SNAKE_ONE_DIMENSIONAL_VECTOR_H
#define SNAKE_ONE_DIMENSIONAL_VECTOR_H

#include <vector>

namespace joaquind {

    using size_t = unsigned long;
    using coord_type = std::pair<size_t, size_t>;

    template<typename T>
    class OneDimensionalVector : public std::vector<T> {
    public:
        OneDimensionalVector() = default;

        explicit OneDimensionalVector(coord_type field_size) : std::vector<T>(field_size.second * field_size.first) {}

        explicit OneDimensionalVector(size_t height, size_t width) : std::vector<T>(height * width) {}

        T &operator()(size_t i, size_t j) { return v_[i * j + j]; }

        std::vector<T> &GetData() { return v_; }

    private:
        std::vector<T> v_{};
    };

} // joaquind

#endif //SNAKE_ONE_DIMENSIONAL_VECTOR_H
