#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include "application.hpp"

#include <fstream>

int main()
{

    engine::Application app{};


    try
    {
        app.run();
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }



    std::cout << "after scope" << std::endl;

    return EXIT_SUCCESS;
}