//
// Created by Joaquina Daeron on 11/28/23.
//

#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/gl.h"
#include "abstract_window.h"
#include "GLFW/glfw3.h"
#include "observer.h"
#include "types.h"

#include <cmath>
#include <sstream>

namespace joaquind {

    class MainWindow : public AbstractWindow, public Observer {
    public:
        MainWindow() : height_{640}, width_{640} {
            instance_ = this;
            type_ = WindowType::kMainWindow;
        }

        void SetParameters(int height, int width, const char *title) {
            height_ = height;
            width_ = width;
            strcpy(title_, title);
        }

        void Init() override {
            SetGLFWSettings();
            CreateWindow();
            SetImguiSettings();
        }

        void Start() {
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//            while (cells_.empty());

            // Main Loop
            while (!glfwWindowShouldClose(window_)) {
                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(640, 640));


                ImGui::Begin("Snake", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
                RenderPrimitives();
                ImGui::End();


                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(window_, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                             clear_color.z * clear_color.w, clear_color.w);
                glClear(GL_COLOR_BUFFER_BIT);

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                glfwSwapBuffers(window_);
            }

            DestroyWindows();
        };

        void RenderPrimitives() {
            ImDrawList *draw_list = ImGui::GetWindowDrawList();
            for (auto &i: cells_) {
                if (i.type == CellType::kBorder) {
                    const ImVec2 pos_start{static_cast<float>((static_cast<float>(i.x) - 0.5) * 10),
                                           static_cast<float>((static_cast<float>(i.y) - 0.5) * 10)};
                    const ImVec2 pos_end{static_cast<float>((static_cast<float>(i.x) + 0.5) * 10),
                                         static_cast<float>((static_cast<float>(i.y) + 0.5) * 10)};
                    ImU32 color = IM_COL32(255, 0, 0, 255);
                    draw_list->AddRectFilled(pos_start, pos_end, color);
                } else if (i.type == CellType::kSnake) {
                    const ImVec2 pos{static_cast<float>(i.x) * 10, static_cast<float>(i.y) * 10};
                    ImU32 color = IM_COL32(0, 0, 255, 255);
                    draw_list->AddCircleFilled(pos, 5, color, 30);
                } else if (i.type == CellType::kMeal) {
                    const ImVec2 pos{static_cast<float>(i.x) * 10, static_cast<float>(i.y) * 10};
                    ImU32 color = IM_COL32(0, 255, 0, 255);
                    draw_list->AddCircleFilled(pos, 5, color, 30);
                }
            }
        }

        void OnUpdate(const std::vector<FieldCell> &cell) override {
            cells_ = cell;
        }

        void AddObserver(KeyObserver *obs) {
            observers_.push_back(obs);
        }

        void RemoveObserver(KeyObserver *obs) {
            observers_.remove(obs);
        }

        void NotifyObservers(char ch) {
            for (auto &i: observers_)
                i->OnKeyPressed(ch);
        }

    private:
        static void ErrorCallback(int error, const char *description) {
            fprintf(stderr, "Error: %s\n", description);
        }

        void DestroyWindows() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwDestroyWindow(window_);
            glfwTerminate();
            exit(0);
        };

        void SetGLFWSettings() {
            // Init start settings
            glfwSetErrorCallback(ErrorCallback);
            if (!glfwInit()) {
                throw std::bad_alloc();
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        }

        void CreateWindow() {
            // Create window, set context
            window_ = glfwCreateWindow(width_, height_, "Hello", nullptr, nullptr);
            if (!window_) {
                glfwTerminate();
                throw std::bad_alloc();
            }
            glfwMakeContextCurrent(window_);
            gladLoadGL(glfwGetProcAddress);
            glfwSwapInterval(1);
            glfwSetKeyCallback(window_, KeyCallback);
        }

        void SetImguiSettings() {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();
            const char *glsl_version = "#version 150";
            ImGui_ImplGlfw_InitForOpenGL(window_, true);
            ImGui_ImplOpenGL3_Init(glsl_version);

            auto io = ImGui::GetIO();
            (void) io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        }

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS) {
                switch (key) {
                    case GLFW_KEY_W:
                        instance_->NotifyObservers('w');
                        break;
                    case GLFW_KEY_A:
                        instance_->NotifyObservers('a');
                        break;
                    case GLFW_KEY_D:
                        instance_->NotifyObservers('d');
                        break;
                    case GLFW_KEY_S:
                        instance_->NotifyObservers('s');
                        break;
                    default:
                        break;
                }
            }
        }

        GLFWwindow *window_{};
        int height_{};
        int width_{};
        char *title_{};
        static MainWindow* instance_;

        std::list<KeyObserver*> observers_{};
        std::vector<FieldCell> cells_{};
    };

    MainWindow *MainWindow::instance_ = nullptr;

}; // joaquind

#endif //SNAKE_WINDOW_H