#include <fstream>
#include <stdexcept>
#include <iostream>

#include "pipeline.hpp"

namespace engine
{
    EnginePipeline::EnginePipeline(const std::string &vertFilePath,
                                   const std::string &fragFilePath)
    {
        creatGraphicsPipeline(vertFilePath, fragFilePath);
    }

    std::vector<char> EnginePipeline::readFile(const std::string &filePath)
    {
        //Open file in bainary input mode and set cursor at the end of file
        std::ifstream file{filePath, std::ios::ate | std::ios::binary | std::ios::in};

        //If file was not found then throw runtime error
        if (!file.is_open())
        {
            throw std::runtime_error{"failed to open file" + filePath};
        }

        //Calculate file size
        size_t file_size = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(file_size);

        //Load file to a vector
        file.seekg(0);
        file.read(buffer.data(), file_size);

        file.close();

        return buffer;
    }

    void EnginePipeline::creatGraphicsPipeline(const std::string &vertFilePath,
                                               const std::string &fragFilePath)
    {
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "VertexCode size is: " << vertCode.size() << std::endl;
        std::cout << "FragmentCode size is: " << fragCode.size() << std::endl;
    }

}