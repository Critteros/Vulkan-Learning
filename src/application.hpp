#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"

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
        EnginePipeline pipeline{
            device,
            "shaders/simple.vert.spv",
            "shaders/simple.frag.spv",
            EnginePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}