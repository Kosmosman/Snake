//
// Created by Joaquina Daeron on 11/28/23.
//

#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <cmath>

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


    class MainWindow : public AbstractWindow {
    public:
        MainWindow() : height_{640}, width_{640} {
            type_ = WindowType::kMainWindow;
        }

        void SetParameters(int height, int width, const char *title) {
            height_ = height;
            width_ = width;
            strcpy(title_, title);
        }

        void Init() override {
            // Init start settings
            glfwSetErrorCallback(ErrorCallback);
            if (!glfwInit()) {
                throw std::bad_alloc();
            }
            const char* glsl_version = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            // Create window, set context
            window_ = glfwCreateWindow(1200, 800, "Hello", nullptr, nullptr);
            if (!window_) {
                glfwTerminate();
                throw std::bad_alloc();
            }
            glfwMakeContextCurrent(window_);
            gladLoadGL(glfwGetProcAddress);
            glfwSwapInterval(1);

            // Set dear ImGui settings
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            auto io = ImGui::GetIO();
            (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window_, true);
            ImGui_ImplOpenGL3_Init(glsl_version);
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            // Main Loop
            while (!glfwWindowShouldClose(window_)) {
                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGui::Begin("Hello World");
                ImGui::End();

                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(window_, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(window_);
            }

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            glfwDestroyWindow(window_);
            glfwTerminate();
        }

    private:
        static void ErrorCallback(int error, const char *description) {
            fprintf(stderr, "Error: %s\n", description);
        }

        GLFWwindow *window_{};
        int height_{};
        int width_{};
        char *title_{};
    };

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

}; // joaquind

#endif //SNAKE_WINDOW_H