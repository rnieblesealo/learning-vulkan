#pragma once

struct GLFWwindow;

namespace veng
{
class Window
{
public:
  Window(std::string name, glm::ivec2 size);
  ~Window();

  glm::ivec2  GetWindowSize() const;
  bool        ShouldClose() const;
  GLFWwindow *GetHandle() const;
  bool        TryMoveToMonitor(std::uint32_t monitor_number);

private:
  GLFWwindow *_window;
};
} // namespace veng