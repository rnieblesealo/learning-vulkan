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

  void                                      InitializeVulkan();
  void                                      CreateInstance();
  static std::vector<gsl::czstring>         GetSuggestedInstanceExtensions();
  static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
  static bool AllExtensionsSupported(gsl::span<gsl::czstring> extensions);

private:
  VkInstance              _instance = nullptr;
  gsl::not_null<Window *> _window; // Our own window class!
};
} // namespace veng