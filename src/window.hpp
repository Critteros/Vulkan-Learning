#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace engine
{
    class EngineWindow
    {
    public:
        EngineWindow(int32_t width, int32_t height, const std::string &window_name);
        ~EngineWindow();

        EngineWindow(const EngineWindow &) = delete;
        EngineWindow &operator=(const EngineWindow &) = delete;

        inline bool shouldClose() { return glfwWindowShouldClose(window); }

    private:
        GLFWwindow *window;
        int32_t width;
        int32_t height;

        std::string window_name;

        void init_window();
    };
}