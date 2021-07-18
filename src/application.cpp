#include "application.hpp"

namespace engine
{
    Application::Application()
    {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    Application::~Application()
    {
        vkDestroyPipelineLayout(device.getDevice(), pipelineLayout, nullptr);
    }

    void Application::run()
    {
        while (!window.shouldClose())
        {
            glfwPollEvents();
        }
    }

    void Application::createPipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;

        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(device.getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error{"Cannot create pipeline layout!"};
        }
    }

    void Application::createPipeline()
    {
        auto pipelineConfig = EnginePipeline::defaultPipelineConfigInfo(swapChain.width(), swapChain.height());
        pipelineConfig.renderPass = swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<EnginePipeline>(
            device,
            "shaders/simple.frag.spv",
            "shaders/simple.vert.spv",
            pipelineConfig);
    }

    void Application::createCommandBuffers()
    {
    }

    void Application::drawFrame()
    {
    }
}