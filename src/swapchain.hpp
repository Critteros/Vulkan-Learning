#pragma once

#include "device.hpp"

namespace engine
{

    class SwapChain
    {
    public:
        SwapChain(EngineDevice &device, VkExtent2D extend);
        ~SwapChain();

        static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

        //Delete copying
        SwapChain(const SwapChain &) = delete;
        SwapChain &operator=(const SwapChain &) = delete;

        inline VkRenderPass getRenderPass() { return renderPass; }
        inline VkImageView getImageView(int index) { return swapChainImageViews[index]; }
        inline size_t imageCount() { return swapChainImages.size(); }
        inline VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
        inline VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
        inline VkExtent2D getSwapChainExtent() { return swapChainExtent; }
        inline uint32_t width() { return swapChainExtent.width; }
        inline uint32_t height() { return swapChainExtent.height; }

        inline float extentAspectRatio()
        {
            return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
        }
        VkFormat findDepthFormat();

        VkResult acquireNextImage(uint32_t *imageIndex);
        VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

    private:
        //Primary functions
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createFramebuffers();
        void createDepthResources();

        //Helper functions
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        //Private Variables
        EngineDevice &device;
        VkExtent2D windowExtend;
        std::vector<VkImage> depthImages;
        std::vector<VkDeviceMemory> depthImageMemorys;
        std::vector<VkImageView> depthImageViews;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        std::vector<VkFramebuffer> swapChainFramebuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
    };

}