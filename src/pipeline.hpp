#pragma once

#include <string>
#include <vector>
#include <cassert>

#include "device.hpp"

namespace engine
{

    struct PipelineConfigInfo
    {
        VkViewport viewport{};
        VkRect2D scissor{};
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
        VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
        VkPipelineMultisampleStateCreateInfo multisampleInfo{};
        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class EnginePipeline
    {
    public:
        EnginePipeline(
            EngineDevice &device,
            const std::string &vertFilePath,
            const std::string &fragFilePath,
            const PipelineConfigInfo &configInfo);

        ~EnginePipeline();

        EnginePipeline(const EnginePipeline &) = delete;
        EnginePipeline &operator=(const EnginePipeline &) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        std::vector<char> readFile(const std::string &filePath);

        void createGraphicsPipeline(const std::string &vertFilePath,
                                    const std::string &fragFilePath,
                                    const PipelineConfigInfo &configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

        EngineDevice &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
        VkPipelineLayout pipelineLayout;
    };
}