#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "application.hpp"

#include <fstream>

int main()
{

    engine::Application app{};

    std::cout << "starting" << std::endl;

    try
    {
        app.run();
    }
    catch (const std::exception &exc)
    {
        std::cerr << exc.what() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}