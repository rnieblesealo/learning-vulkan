#include <GLFW/glfw3.h>

#include "glfw-monitor.h"
#include "glfw-window.h"

namespace veng
{
gsl::span<GLFWmonitor *> GetMonitors()
{
  std::int32_t  monitor_count(0);
  GLFWmonitor **monitor_pointers = glfwGetMonitors(&monitor_count);

  return gsl::span<GLFWmonitor *>(monitor_pointers, monitor_count);
}

glm::ivec2 GetMonitorPosition(gsl::not_null<GLFWmonitor *> monitor)
{
  glm::ivec2 monitor_pos;

  glfwGetMonitorPos(monitor, &monitor_pos.x, &monitor_pos.y); // Get main monitor

  return monitor_pos;
}

glm::ivec2 GetMonitorWorkAreaSize(gsl::not_null<GLFWmonitor *> monitor)
{
  glm::ivec2 monitor_size;

  glfwGetMonitorWorkarea(
      monitor, nullptr, nullptr, &monitor_size.x, &monitor_size.y); // Get its size

  return monitor_size;
}

void MoveWindowToMonitor(gsl::not_null<GLFWwindow *> window, gsl::not_null<GLFWmonitor *> monitor)
{
  glm::ivec2 window_size;

  glfwGetWindowSize(window, &window_size.x, &window_size.y);

  // Put window at center
  glm::vec2 new_window_pos = veng::GetMonitorPosition(monitor) +
                             (veng::GetMonitorWorkAreaSize(monitor) / 2) - (window_size / 2);

  glfwSetWindowPos(window, new_window_pos.x, new_window_pos.y);
}
} // namespace veng