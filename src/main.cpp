#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <spdlog/spdlog.h>

#include "application.hpp"

int main()
{

    engine::Application app{};

    try
    {
        app.run();
    }
    catch (const std::exception &exc)
    {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}