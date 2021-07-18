#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swapchain.hpp"

#include <memory>
#include <vector>

namespace engine
{
    class Application
    {
    public:
        static constexpr int32_t WIDTH = 800;
        static constexpr int32_t HEIGHT = 600;

        void run();

    private:
        EngineWindow window{WIDTH, HEIGHT, "Vulkan Window"};
        EngineDevice device{window};
        SwapChain swapChain{device, window.getExtend()};
        std::unique_ptr<EnginePipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}