#include <GLFW/glfw3.h>

#include "glfw-initialization.h"
#include "glfw-window.h"
#include "graphics.h"
#include "precomp.h"

namespace
{
const uint32_t WINDOW_WIDTH  = 500;
const uint32_t WINDOW_HEIGHT = 500;
} // namespace

std::int32_t main(std::int32_t argc, gsl::zstring *argv)
{
  // Initialize GLFW with RAII
  veng::GlfwInitialization _glfw;

  // Initialize window
  veng::Window window("Vulkan Engine", {WINDOW_WIDTH, WINDOW_HEIGHT});

  // Move window to first monitor
  window.TryMoveToMonitor(0);

  // Initialize graphics engine
  veng::Graphics graphics(&window);

  // Main loop
  while (!window.ShouldClose())
  {
    glfwPollEvents(); // Need this for window to show
  }

  return EXIT_SUCCESS;
}