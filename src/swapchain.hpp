#pragma once

#include "device.hpp"

namespace engine
{

    class SwapChain
    {
    public:
        SwapChain(EngineDevice &device, VkExtent2D extend);
        ~SwapChain();

        //Delete copying
        SwapChain(const SwapChain &) = delete;
        SwapChain &operator=(const SwapChain &) = delete;

    private:
        //Primary functions
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createFramebuffers();

        //Helper functions
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        //Private Variables
        EngineDevice &device;
        VkExtent2D windowExtend;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        std::vector<VkFramebuffer> swapChainFramebuffers;
    };

}