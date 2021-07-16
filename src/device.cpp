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

        uint32_t extensionCount = static_cast<uint32_t>(requiredExtensions.size());

        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();
        createInfo.enabledLayerCount = 0;

        VkResult instanceCreateInfo = vkCreateInstance(&createInfo, nullptr, &instance);

        if (instanceCreateInfo != VK_SUCCESS)
            throw std::runtime_error{"failure in creating vulkan instance"};

        checkExtensions();
    }

    void EngineDevice::checkExtensions()
    {
        uint32_t extensionCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

        std::unordered_set<const char *> supportedExtensions;
        const char *extensionName;

        std::cout << "\nSupported Extensions:" << std::endl;

        for (auto el : availableExtensions)
        {
            extensionName = el.extensionName;
            supportedExtensions.emplace(extensionName);
            std::cout << extensionName << std::endl;
        }

        auto requiredExtensions = getRequiredExtensions();
        std::cout << "\nRequired Extensions" << std::endl;
        for (auto el : requiredExtensions)
        {
            if (supportedExtensions.find(el) == supportedExtensions.end())
                std::runtime_error{"Required extension could not be found"};

            std::cout << el << std::endl;
        }
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