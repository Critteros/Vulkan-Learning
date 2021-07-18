#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swapchain.hpp"

#include <memory>
#include <vector>
#include <stdexcept>
#include <array>

namespace engine
{
    class Application
    {
    public:
        static constexpr int32_t WIDTH = 800;
        static constexpr int32_t HEIGHT = 600;

        Application();
        ~Application();

        //Delete copy constructors
        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        void run();

    private:
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        EngineWindow window{WIDTH, HEIGHT, "Vulkan Window"};
        EngineDevice device{window};
        EngineSwapChain swapChain{device, window.getExtend()};
        std::unique_ptr<EnginePipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}