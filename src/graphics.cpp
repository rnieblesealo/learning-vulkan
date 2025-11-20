#include <GLFW/glfw3.h>

#include "graphics.h"
#include "precomp.h"

veng::Graphics::Graphics(gsl::not_null<Window *> window)
    : _window(window)
{
  InitializeVulkan();
}

veng::Graphics::~Graphics() {}

void veng::Graphics::InitializeVulkan() { CreateInstance(); }

void veng::Graphics::CreateInstance()
{
  // Set info about this app
  VkApplicationInfo app_info;

  app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext              = nullptr; // No extensions to app info
  app_info.pApplicationName   = "Vulkan Engine";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName        = "VEng";
  app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion         = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_creation_info{};

  instance_creation_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_creation_info.pNext            = nullptr;
  instance_creation_info.pApplicationInfo = &app_info;

  // Get extensions
  std::vector<gsl::czstring> suggested_extensions = GetSuggestedExtensions();

  bool vksp = glfwVulkanSupported() == GLFW_TRUE;

  // Add extension required by MoltenVK
  suggested_extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

  instance_creation_info.enabledExtensionCount   = suggested_extensions.size();
  instance_creation_info.ppEnabledExtensionNames = suggested_extensions.data();

  // Set flag required by macOS MoltenVK
  instance_creation_info.flags =
      VkInstanceCreateFlagBits::VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

  instance_creation_info.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&instance_creation_info, nullptr, &_instance);

  if (result != VK_SUCCESS)
  {
    std::exit(EXIT_FAILURE);
  }
}

std::vector<gsl::czstring> veng::Graphics::GetSuggestedExtensions()
{
  // Get GLFW extensions
  std::uint32_t  glfw_extension_count(0);
  gsl::czstring *glfw_extensions;

  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  // Return as vector so we can add more extensions if needed
  std::vector<gsl::czstring> res;

  for (gsl::czstring *ext; ext != nullptr; ++ext)
  {
    res.push_back(gsl::czstring(ext));
  }

  return res;
}