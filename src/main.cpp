#include <GLFW/glfw3.h>

#include "glfw-initialization.h"
#include "glfw-monitor.h"

namespace
{
const uint32_t WINDOW_WIDTH  = 500;
const uint32_t WINDOW_HEIGHT = 500;
} // namespace

std::int32_t main(std::int32_t argc, gsl::zstring *argv)
{
  // Initialize GLFW with RAII
  veng::GlfwInitialization _glfw;

  // Create window
  gsl::not_null<GLFWwindow *> window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan Engine", nullptr, nullptr);

  // Capture window var by value; lambda func
  // final_action runs the passed func when destructor (of window) is reached
  gsl::final_action _cleanup_window([window] { glfwDestroyWindow(window); });

  // Get main monitor
  gsl::span<GLFWmonitor *> monitors = veng::GetMonitors();

  // If more than 1 monitor, ensure our window is at center of main monitor
  if (monitors.size() > 1)
  {
    // Move window to center of it
    veng::MoveWindowToMonitor(window, monitors[0]);
  }

  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents(); // Need this for window to show
  }

  return EXIT_SUCCESS;
}