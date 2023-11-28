//
// Created by Joaquina Daeron on 11/28/23.
//

#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include <cmath>

namespace joaquind {

    class Window {
    public:
        void Init() {
            GLFWwindow *window{};
            if (!glfwInit())
                throw std::invalid_argument("Not initialize");
            window = glfwCreateWindow(640, 480, "hello World", nullptr, nullptr);
            if (!window) {
                glfwTerminate();
                throw std::invalid_argument("Not initialize");
            }
            glfwMakeContextCurrent(window);

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            while (!glfwWindowShouldClose(window)) {}

        }
    };

}; // joaquind

#endif //SNAKE_WINDOW_H