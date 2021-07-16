#include <iostream>
#include <stdexcept>

#include "device.hpp"
namespace engine
{
    EngineDevice::EngineDevice(EngineWindow &window) : window{window}
    {
        createInstance();
    }

    void EngineDevice::createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "My Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto requiredExtensions = getRequiredExtensions();

        std::cout << "Required Extensions:" << std::endl;

        for (auto el : requiredExtensions)
            std::cout << el << std::endl;

        uint32_t extensionCount = static_cast<uint32_t>(requiredExtensions.size());

        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
        createInfo.enabledLayerCount = 0;

        VkResult instanceCreateInfo = vkCreateInstance(&createInfo, nullptr, &instance);

        if (instanceCreateInfo != VK_SUCCESS)
            throw std::runtime_error("failure in creating vulkan instance");
    }

    std::vector<const char *> EngineDevice::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        return extensions;
    }
}