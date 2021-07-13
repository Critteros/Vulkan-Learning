#include "application.hpp"

namespace engine
{
    void Application::run()
    {
        while (!window.shouldClose())
        {
            glfwPollEvents();
        }
    }
}