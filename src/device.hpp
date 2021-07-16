#pragma once

#include <vector>
#include <unordered_set>
#include <iostream>
#include <cstring>

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
        bool checkValidationLayerSupport();
        std::vector<const char *> getRequiredExtensions();

        EngineWindow &window;
        VkInstance instance;
        const bool enableValidationLayers = true;
        const std::vector<const char *> validationLayers{
            "VK_LAYER_KHRONOS_validation"};
    };
}