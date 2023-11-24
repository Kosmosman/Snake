//
// Created by Joaquina Daeron on 11/24/23.
//

#ifndef SNAKE_TRANSFORMATOR_H
#define SNAKE_TRANSFORMATOR_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "components/abstract_object.h"
#include "components/field.h"

namespace joaquind {

    using coord_type = std::pair<size_t, size_t>;

    class Transformator {
    public:
        explicit Transformator(coord_type field_size) : message_(field_size.second,
                                                                 std::string(field_size.first, ' ')) {}

        void TransformFieldToString(std::unordered_map<size_t, std::shared_ptr<Field>> &objects) {
            for (auto &[id, object]: objects) {
                auto obj_ptr = object->GetData();
                for (int i{}; i < obj_ptr.size(); ++i) {
                    for (int j{}; j < obj_ptr[0].size(); ++j) {
                        message_[i][j] = obj_ptr[i][j];
                    }
                }
            }
        }

        void TransformSnakeToString(std::unordered_map<size_t, std::shared_ptr<Snake>> &objects) {
            for (auto &[id, object]: objects) {
                auto obj_ptr = object->GetData();
                for (auto &i: obj_ptr) {
                    message_[i.first][i.second] = Field::kFieldType::SNAKE;
                }
            }
        }

        void TransformMealToString(std::unordered_map<size_t, std::shared_ptr<Meal>> &objects) {
            for (auto &[id, object]: objects) {
                auto obj_ptr = object->GetData();
                for (auto &i: obj_ptr) {
                    message_[i.first][i.second] = Field::kFieldType::MEAL;
                }
            }
        }

        std::string GetData() {
            std::ostringstream oss;
            std::copy(message_.begin(), message_.end(), std::ostream_iterator<std::string>(oss, "\n"));
            return oss.str();
        };

    private:
        std::vector<std::string> message_{};
    };

} // joaquind

#endif //SNAKE_TRANSFORMATOR_H
