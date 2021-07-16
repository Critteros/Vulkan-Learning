#pragma once

#include <vector>
#include <unordered_set>
#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <optional>

#include <spdlog/spdlog.h>

#include "window.hpp"

namespace engine
{

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        inline bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class EngineDevice
    {
    public:
        EngineDevice(EngineWindow &window);
        ~EngineDevice();

        //Do not allow copying
        EngineDevice(const EngineDevice &) = delete;
        EngineDevice &operator=(const EngineDevice &) = delete;

    private:
        //Primary setup functions
        void createInstance();
        void setupDebugMessenger();
        void pickPhysicalDevice();
        void createSurface();
        void createSwapChain();

        //Helper functions
        void checkExtensions();
        void createLogicalDevice();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        int rateDeviceSuitability(VkPhysicalDevice device);
        bool isDeviceSuitable(VkPhysicalDevice device);
        void createImageViews();
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        bool checkValidationLayerSupport();
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        std::vector<const char *> getRequiredExtensions();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

        //Private variables
        EngineWindow &window;
        VkInstance instance;
        VkQueue graphicsQueue;
        VkSurfaceKHR surface;
        VkQueue presentQueue;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice logicalDevice;
        const bool enableValidationLayers = true;
        const std::vector<const char *> validationLayers{
            "VK_LAYER_KHRONOS_validation"};

        const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME};

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