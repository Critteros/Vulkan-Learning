#pragma once

#include <string>
#include <vector>

namespace engine
{
    class EnginePipeline
    {
    public:
        EnginePipeline(
            const std::string &vertFilePath,
            const std::string &fragFilePath);

    private:
        std::vector<char> readFile(const std::string &filePath);

        void creatGraphicsPipeline(const std::string &vertFilePath,
                                   const std::string &fragFilePath);
    };
}