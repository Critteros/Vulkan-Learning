cmake_minimum_required(VERSION 3.10)

#Project initial-setup
project("Vulkan-learning" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
message("${CMAKE_MODULE_PATH}nn")
#find_package(glfw3 CONFIG REQUIRED)
find_library(GLFW 
    NAMES glfw3.lib
    PATHS "C:\\dev-Tools\\GLFW\\3.3.4\\lib-vc2019" 
    REQUIRED)


add_executable(${PROJECT_NAME} main.cpp)