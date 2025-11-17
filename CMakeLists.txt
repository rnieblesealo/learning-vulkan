cmake_minimum_required(VERSION 4.0)

project(VulkanEngine)

set(CMAKE_BUILD_TYPE Debug)

# Get VK install
find_package(Vulkan REQUIRED)

# Include FetchContent extension module
include(FetchContent)

# Declare a new dependency (GLM)
FetchContent_Declare(
    glm
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG "1.0.2" # Concrete version; see repo tag page
    GIT_SHALLOW TRUE # Only pull latest snapshot (i.e. one checkout) to reduce overhead
)

# Make it available for linking
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw"
    GIT_TAG "3.4"
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    microsoft-gsl
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.2.0"
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(microsoft-gsl)

# Add any files in src/ to the final binary 
# CONFIGURE_DEPENDS = If any files change, rerun config step for target(s)
file(GLOB_RECURSE VulkanEngineSources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(VulkanEngine
    "${VulkanEngineSources}"
)

# Link VK
target_link_libraries(VulkanEngine PRIVATE
    "Vulkan::Vulkan"
    glm
    glfw
    Microsoft.GSL::GSL 
)

# C++20 for VulkanEngine target 
target_compile_features(VulkanEngine PRIVATE cxx_std_20)
