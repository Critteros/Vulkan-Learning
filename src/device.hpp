#pragma once

#include <vector>
#include <unordered_set>
#include <iostream>
#include <cstring>

#include <spdlog/spdlog.h>

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
        void setupDebugMessenger();
        bool checkValidationLayerSupport();
        std::vector<const char *> getRequiredExtensions();

        EngineWindow &window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        const bool enableValidationLayers = true;
        const std::vector<const char *> validationLayers{
            "VK_LAYER_KHRONOS_validation"};

        //Custom Debug callback
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void *pUserData);

        //Proxy functions
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                              const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                              const VkAllocationCallbacks *pAllocator,
                                              VkDebugUtilsMessengerEXT *pDebugMessenger);

        void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                           VkDebugUtilsMessengerEXT debugMessenger,
                                           const VkAllocationCallbacks *pAllocator);
    };
}