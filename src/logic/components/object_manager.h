//
// Created by Joaquina Daeron on 11/24/23.
//

#ifndef SNAKE_OBJECT_MANAGER_H
#define SNAKE_OBJECT_MANAGER_H

#include "field.h"
#include "meal.h"
#include "snake.h"
#include "object_builder.h"

#include <unordered_map>

namespace joaquind {

    struct ObjectCounter {
        size_t snake_counter{};
        size_t field_counter{};
        size_t meal_counter{};
    };

    class ObjectManager {
    public:
        template<typename T>
        void Create(coord_type field_size) {
            ObjectBuilder<T> builder_{};
            if constexpr (std::is_same_v<T, Snake>)
                snakes_[counter_.snake_counter++] = builder_.Create(field_size);
            else if constexpr (std::is_same_v<T, Field>)
                fields_[counter_.field_counter++] = builder_.Create(field_size);
            else
                meals_[counter_.meal_counter++] = builder_.Create(field_size);
        }

        template<typename T>
        void Remove(size_t object_id) {
            if constexpr (std::is_same_v<T, Snake>)
                snakes_.erase(object_id);
            else if constexpr (std::is_same_v<T, Field>)
                fields_.erase(object_id);
            else
                meals_.erase(object_id);
        }

        template<typename T>
        std::unordered_map<size_t, std::shared_ptr<T>> &Get() {
            if constexpr (std::is_same_v<T, Snake>)
                return snakes_;
            else if constexpr (std::is_same_v<T, Field>)
                return fields_;
            else
                return meals_;
        }

    protected:
        ObjectCounter counter_{};
        std::unordered_map<size_t, std::shared_ptr<Snake>> snakes_{};
        std::unordered_map<size_t, std::shared_ptr<Field>> fields_{};
        std::unordered_map<size_t, std::shared_ptr<Meal>> meals_{};

    };

} // joaquind

#endif //SNAKE_OBJECT_MANAGER_H
