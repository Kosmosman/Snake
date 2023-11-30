//
// Created by Joaquina Daeron on 11/30/23.
//

#ifndef SNAKE_ABSTRACT_WINDOW_H
#define SNAKE_ABSTRACT_WINDOW_H

namespace joaquind {

    class AbstractWindow {
    public:
        enum class WindowType {
            kBasicWindow,
            kMainWindow
        };

        virtual ~AbstractWindow() = default;

        virtual void Init() = 0;

        [[nodiscard]] const WindowType& GetType() const noexcept { return type_; }

    protected:
        WindowType type_{WindowType::kBasicWindow};
    };


} // joaquind

#endif //SNAKE_ABSTRACT_WINDOW_H
