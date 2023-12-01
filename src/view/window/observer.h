//
// Created by Joaquina Daeron on 11/30/23.
//

#ifndef SNAKE_OBSERVER_H
#define SNAKE_OBSERVER_H
#include <vector>
#include <types.h>

namespace joaquind {
    class Observer {
    public:
        virtual void OnUpdate(const std::vector<FieldCell>&) = 0;
    };


} // joaquind

#endif //SNAKE_OBSERVER_H
