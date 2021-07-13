#pragma once

#include "window.hpp"
#include "pipeline.hpp"

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
        EnginePipeline pipeline{"shaders/simple.vert.spv", "shaders/simple.frag.spv"};
    };
}