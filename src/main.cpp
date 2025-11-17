#include <GLFW/glfw3.h>
#include <cstdint>
#include <gsl/gsl>
#include <iostream>

#include "glfw-initialization.h"

namespace
{
uint32_t SCREEN_WIDTH  = 500;
uint32_t SCREEN_HEIGHT = 500;
} // namespace

std::int32_t main(std::int32_t argc, gsl::zstring *argv)
{
  // Initialize GLFW with RAII
  veng::GlfwInitialization _glfw;

  // Create window
  gsl::not_null<GLFWwindow *> window =
      glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Vulkan Engine", nullptr, nullptr);

  // Capture window var by value; lambda func
  // final_action runs the passed func when destructor (of window) is reached
  gsl::final_action _cleanup_window([window] { glfwDestroyWindow(window); });

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents(); // Need this for window to show
  }

  return EXIT_SUCCESS;
}