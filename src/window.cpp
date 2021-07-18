#include "window.hpp"

namespace engine
{
    EngineWindow::EngineWindow(int32_t width, int32_t height, const std::string &window_name)
        : width{width}, height{height}, window_name{window_name}
    {
        init_window();
    }

    void EngineWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error{"failed to create window surface"};
        }
    }

        void EngineWindow::init_window()
    {
        glfwInit();

        //GLFW Hints
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //Do not create OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);   //Window is not resizable

        window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    }

    EngineWindow::~EngineWindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}