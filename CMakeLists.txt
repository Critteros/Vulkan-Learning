cmake_minimum_required(VERSION 3.10)


#Project initial-setup
project("Vulkan-Learning" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#Folder in which resides external libraries
set(vendor_DIR "${PROJECT_SOURCE_DIR}/vendor")


# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h" "src/*.c")
add_executable(${PROJECT_NAME} ${sources})


#########################################################################
# Load Dependecies                                                      #
#########################################################################
set(project-deps-list)


# Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

# GLM
set(glm_DIR "${vendor_DIR}/glm/cmake/glm")
find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# GLFW 
set(GLFW_USE_HYBRID_HPG OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
set(GLFW_UNINSTALL      OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC  OFF CACHE BOOL "" FORCE)
add_subdirectory("${vendor_DIR}/GLFW")
list(APPEND project-deps-list glfw)

#########################################################################


# Add properties to dependencies
#########################################################################

foreach(target ${project-deps-list})
    set_target_properties(${target}
    PROPERTIES 
        FOLDER "external-library"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        )
endforeach(target ${project-deps-list})

#########################################################################
#########################################################################

#Linking dependencies
add_library(project-deps INTERFACE)
foreach(target ${project-deps-list})
    target_link_libraries(project-deps INTERFACE ${target})
endforeach()
target_link_libraries(${PROJECT_NAME} PRIVATE project-deps)



#Advanced setup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )


#Preprocessor Defines
add_compile_definitions(GLFW_INCLUDE_NONE)


