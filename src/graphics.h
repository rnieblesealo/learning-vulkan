#pragma once

#include <vulkan/vulkan.h>

class Window;

namespace veng
{
class Graphics final
{
public:
  Graphics(gsl::not_null<Window *> window);
  ~Graphics();

  void                     InitializeVulkan();
  void                     CreateInstance();
  gsl::span<gsl::czstring> GetSuggestedExtensions();

private:
  VkInstance              _instance;
  gsl::not_null<Window *> _window; // Our own window class!
};
} // namespace veng