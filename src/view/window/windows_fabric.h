//
// Created by Joaquina Daeron on 11/30/23.
//

#ifndef SNAKE_WINDOWS_FABRIC_H
#define SNAKE_WINDOWS_FABRIC_H

#include "window.h"


namespace joaquind {

    class WindowsFabric {
    public:
        AbstractWindow *Create(AbstractWindow::WindowType type) {
            switch (type) {
                case AbstractWindow::WindowType::kMainWindow:
                    return new MainWindow;
                default:
                    return nullptr;
            }
        }
    };

} // joaquind

#endif //SNAKE_WINDOWS_FABRIC_H
