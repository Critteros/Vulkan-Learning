cmake_minimum_required(VERSION 3.10)
project("Vulkan-learning" LANGUAGES CXX)


#Conan
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
    REQUIRES
    
    fmt/8.0.1
    glfw/3.3.4
    glm/0.9.9.8

    BASIC_SETUP CMAKE_TARGETS
)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(${PROJECT_NAME} main.cpp)

find_package(Vulkan REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    CONAN_PKG::fmt
    CONAN_PKG::glfw
    CONAN_PKG::glm
    Vulkan::Vulkan
    )