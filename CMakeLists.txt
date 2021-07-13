cmake_minimum_required(VERSION 3.10)


#Project initial-setup
project("Vulkan-Learning" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h" "src/*.c")
add_executable(${PROJECT_NAME} ${sources})


if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")
endif()

#########################################################################
# Load Dependecies                                                      #
#########################################################################
set(external_DIR "${PROJECT_SOURCE_DIR}/vendor")
set(external_INCLUDE "${external_DIR}/include")
set(external_LIB "${external_DIR}/lib")


message("${external_LIB}")



# GLFW 
target_link_libraries(${PROJECT_NAME} PRIVATE "${external_LIB}/glfw3.lib")

# GLM
target_include_directories(${PROJECT_NAME} PRIVATE "${external_INCLUDE}")


# Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

#########################################################################





#Advanced setup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )


#Preprocessor Defines
add_compile_definitions(GLFW_INCLUDE_NONE)


