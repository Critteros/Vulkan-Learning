#pragma once

#include <vector>

#include "window.hpp"

namespace engine
{

    class EngineDevice
    {
    public:
        EngineDevice(EngineWindow &window);

        //Do not allow copying
        EngineDevice(const EngineDevice &) = delete;
        EngineDevice &operator=(const EngineDevice &) = delete;

    private:
        void createInstance();
        std::vector<const char *> getRequiredExtensions();

        EngineWindow &window;
        VkInstance instance;
    };
}