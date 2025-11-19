#pragma once

#include "glfw-window.h"

#include <vulkan/vulkan.h>

namespace veng
{
class Graphics final
{
public:
  Graphics(gsl::not_null<Window *> window);
  ~Graphics();

  void                       InitializeVulkan();
  void                       CreateInstance();
  std::vector<gsl::czstring> GetSuggestedExtensions();

private:
  VkInstance              _instance;
  gsl::not_null<Window *> _window; // Our own window class!
};
} // namespace veng