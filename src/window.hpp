#pragma once

#include <stdexcept>
#include <algorithm>

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

        //Do not allow copying object of this class
        EngineWindow(const EngineWindow &) = delete;
        EngineWindow &operator=(const EngineWindow &) = delete;

        inline bool shouldClose() { return glfwWindowShouldClose(window); }
        inline VkExtent2D getExtend() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        GLFWwindow *window;
        int32_t width;
        int32_t height;

        std::string window_name;

        void init_window();
    };
}