#include <GLFW/glfw3.h>

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

  std::int32_t             monitor_count(0);
  gsl::span<GLFWmonitor *> monitors(glfwGetMonitors(&monitor_count), monitor_count);

  glm::ivec2 main_monitor_logical_pos;
  glfwGetMonitorPos(
      monitors[0], &main_monitor_logical_pos.x, &main_monitor_logical_pos.y); // Get main monitor
  glfwSetWindowPos(
      window, main_monitor_logical_pos.x, main_monitor_logical_pos.y); // Move window to its pos

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents(); // Need this for window to show
  }

  return EXIT_SUCCESS;
}