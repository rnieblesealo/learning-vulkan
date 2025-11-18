#include <GLFW/glfw3.h>

#include "glfw-monitor.h"
#include "glfw-window.h"

namespace veng
{
Window::Window(std::string name, glm::ivec2 size)
{
  _window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);
  if (_window == nullptr)
  {
    std::exit(EXIT_FAILURE);
  }
}

Window::~Window() { glfwDestroyWindow(_window); }

glm::ivec2 Window::GetWindowSize() const
{
  glm::ivec2 window_size;

  glfwGetWindowSize(_window, &window_size.x, &window_size.y);

  return window_size;
}

bool Window::ShouldClose() const { return glfwWindowShouldClose(_window); }

GLFWwindow *Window::GetHandle() const { return _window; }

bool Window::TryMoveToMonitor(std::uint32_t monitor_number)
{
  gsl::span<GLFWmonitor *> monitors = veng::GetMonitors();
  if (monitor_number > monitors.size())
  {
    veng::MoveWindowToMonitor(_window, monitors[monitor_number]);
    return true;
  }

  return false;
}
} // namespace veng
