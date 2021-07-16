#include "device.hpp"

namespace engine
{
    EngineDevice::EngineDevice(EngineWindow &window) : window{window}
    {
        createInstance();
        setupDebugMessenger();
    }

    EngineDevice::~EngineDevice()
    {
        if (enableValidationLayers)
        {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }

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

        checkExtensions();
        //Creating vulkan instance
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            throw std::runtime_error{"failure in creating vulkan instance"};
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

    void EngineDevice::setupDebugMessenger()
    {
        if (!enableValidationLayers)
            return;

        //Debug Messanger create info
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr; // Optional

        if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
        {
            throw std::runtime_error{"failed to set up debug messenger!"};
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

        //Retriving GLFW extensions
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        //Adding extension for debug
        if (enableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL EngineDevice::debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData)
    {
        switch (messageSeverity)
        {
        case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT):
            spdlog::debug("{}\n", pCallbackData->pMessage);
            break;

        case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT):
            spdlog::info("{}\n", pCallbackData->pMessage);
            break;

        case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT):
            spdlog::warn("{}\n", pCallbackData->pMessage);
            break;

        case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT):
            spdlog::error("{}\n", pCallbackData->pMessage);
            break;

        default:
            break;
        }

        return VK_FALSE;
    }

    VkResult EngineDevice::CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                        const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                        const VkAllocationCallbacks *pAllocator,
                                                        VkDebugUtilsMessengerEXT *pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void EngineDevice::DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                                     VkDebugUtilsMessengerEXT debugMessenger,
                                                     const VkAllocationCallbacks *pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }
}