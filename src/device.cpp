#include "device.hpp"

namespace engine
{
    EngineDevice::EngineDevice(EngineWindow &window) : window{window}
    {
        createInstance();
    }

    EngineDevice::~EngineDevice()
    {
        vkDestroyInstance(instance, nullptr);
    }

    void EngineDevice::createInstance()
    {
        if (enableValidationLayers && !checkValidationLayerSupport())
            throw std::runtime_error{"Vulkan validation layers are not found\n Propably missing Vulkan SDK\n"};

        //Application information
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "My Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //Getting required extensions for vulkan application
        auto requiredExtensions = getRequiredExtensions();
        uint32_t extensionCount = static_cast<uint32_t>(requiredExtensions.size());

        //Create application info
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extensionCount;
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        if (enableValidationLayers)
        {

            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        //Creating vulkan instance
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            throw std::runtime_error{"failure in creating vulkan instance"};

        checkExtensions();
    }

    void EngineDevice::checkExtensions()
    {
        //Get all supported extensions
        uint32_t extensionCount;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());

        //Place for the names of supported extensions
        std::unordered_set<std::string> supportedExtensions;
        const char *extensionName;

        //Listing supported Extensions
        std::cout << "\nSupported Extensions:" << std::endl;
        for (auto el : availableExtensions)
        {
            extensionName = el.extensionName;
            supportedExtensions.insert(extensionName);
            std::cout << extensionName << std::endl;
        }

        //Adding extension for validation layer
        auto requiredExtensions = getRequiredExtensions();
        if (enableValidationLayers)
            requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        //Lising Required extensions
        std::cout
            << "\nRequired Extensions" << std::endl;
        for (auto el : requiredExtensions)
        {
            if (supportedExtensions.find(el) == supportedExtensions.end())
                throw std::runtime_error{"Required extension could not be found"};

            std::cout << el << std::endl;
        }
    }

    bool EngineDevice::checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName : validationLayers)
        {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
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