#pragma once

#include <vector>
#include <unordered_set>
#include <iostream>

#include "window.hpp"

namespace engine
{

    class EngineDevice
    {
    public:
        EngineDevice(EngineWindow &window);
        ~EngineDevice();

        //Do not allow copying
        EngineDevice(const EngineDevice &) = delete;
        EngineDevice &operator=(const EngineDevice &) = delete;

    private:
        void createInstance();
        void checkExtensions();
        std::vector<const char *> getRequiredExtensions();

        EngineWindow &window;
        VkInstance instance;
    };
}