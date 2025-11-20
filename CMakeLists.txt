cmake_minimum_required(VERSION 4.0)

project(VulkanEngine)

set(CMAKE_BUILD_TYPE Debug)

# ==================================================================================================
# ADDING SOURCES
# ==================================================================================================

# Add any files in src/ to the final binary 
# CONFIGURE_DEPENDS = If any files change, rerun config step for target(s)
file(GLOB_RECURSE VulkanEngineSources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(VulkanEngine
    "${VulkanEngineSources}"
)

# ==================================================================================================
# ADDING LIBRARIES 
# ==================================================================================================

find_package(Vulkan REQUIRED)

# Include FetchContent extension module
include(FetchContent)

# Use system install of GLFW for macOS since it is compiled correctly for this platform
# I am not sure how to use FetchContent to compile it such that it works on Mac :(
# Derived this from: https://github.com/glfw/glfw/issues/1248
if(APPLE)
    find_package(glfw3 3.4 REQUIRED)
else()
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw"
        GIT_TAG "3.4"
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(glfw)
endif()

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
    microsoft-gsl
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.2.0"
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(microsoft-gsl)

target_link_libraries(VulkanEngine PRIVATE
    "Vulkan::Vulkan"
    glfw
    glm
    Microsoft.GSL::GSL 
)

# C++20 for VulkanEngine target 
target_compile_features(VulkanEngine PRIVATE cxx_std_20)

# Precompile the includes in precomp.h
# This means they get compiled once in one build and never again
# Speeds up compilation times!
# Also doesn't require us to explicitly #include stuff again
target_precompile_headers(VulkanEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/precomp.h")