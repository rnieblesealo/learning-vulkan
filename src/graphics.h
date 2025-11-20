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
  std::vector<gsl::czstring>                GetInstanceExtensions();
  static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
  static bool AllExtensionsSupported(gsl::span<gsl::czstring> extensions);
  static bool ExtensionMatchesName(gsl::czstring name, VkExtensionProperties const &properties);
  static bool IsExtensionSupported(gsl::span<VkExtensionProperties> extensions, gsl::czstring name);

private:
  VkInstance              _instance = nullptr;
  gsl::not_null<Window *> _window; // Our own window class!
  bool                    _validation_enabled   = false;
  bool                    _moltenvk_fix_enabled = false;
};
} // namespace veng