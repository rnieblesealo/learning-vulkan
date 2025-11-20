#include <GLFW/glfw3.h>

#include "graphics.h"
#include "precomp.h"
#include "utilities.h"

veng::Graphics::Graphics(gsl::not_null<Window *> window)
    : _window(window)
{
  InitializeVulkan();
}

veng::Graphics::~Graphics()
{
  if (_instance != nullptr)
  {
    vkDestroyInstance(_instance, nullptr);
  }
}

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

  instance_creation_info.sType             = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_creation_info.pNext             = nullptr;
  instance_creation_info.pApplicationInfo  = &app_info;
  instance_creation_info.enabledLayerCount = 0;

  // Add extensions
  std::vector<gsl::czstring> suggested_extensions = GetSuggestedInstanceExtensions();

  if (!AllExtensionsSupported(suggested_extensions))
  {
    std::exit(EXIT_FAILURE);
  }

  instance_creation_info.enabledExtensionCount   = suggested_extensions.size();
  instance_creation_info.ppEnabledExtensionNames = suggested_extensions.data();

// Set flag required by macOS MoltenVK
#if defined(__APPLE__)
  instance_creation_info.flags =
      VkInstanceCreateFlagBits::VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#else
  instance_creation_info.flags = nullptr;
#endif

  VkResult result = vkCreateInstance(&instance_creation_info, nullptr, &_instance);

  if (result != VK_SUCCESS)
  {
    std::exit(EXIT_FAILURE);
  }
}

std::vector<gsl::czstring> veng::Graphics::GetSuggestedInstanceExtensions()
{
  // Get GLFW extensions first
  std::uint32_t  glfw_ext_count(0);
  gsl::czstring *glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

  glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

  // Vectorize so we can add more
  std::vector<gsl::czstring> exts(glfw_exts, glfw_exts + glfw_ext_count);

// Add compatibility required by MoltenVK
#if defined(__APPLE__)
  exts.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

  return exts;
}

std::vector<VkExtensionProperties> veng::Graphics::GetSupportedInstanceExtensions()
{
  // Pull extension count first
  std::uint32_t ext_count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, nullptr);

  if (ext_count == 0)
  {
    return {};
  }

  // If any exist return them
  std::vector<VkExtensionProperties> supported_exts(ext_count);
  vkEnumerateInstanceExtensionProperties(nullptr, &ext_count, supported_exts.data());

  return supported_exts;
}

bool veng::Graphics::AllExtensionsSupported(gsl::span<gsl::czstring> extensions)
{
  std::vector<VkExtensionProperties> supported_extensions = GetSupportedInstanceExtensions();

  // Make sure they are all supported
  auto is_extension_supported = [&supported_extensions](gsl::czstring name)
  {
    return std::any_of(supported_extensions.begin(),
                       supported_extensions.end(),
                       [name](VkExtensionProperties const &property)
                       { return streq(property.extensionName, name); });
  };

  return std::all_of(extensions.begin(), extensions.end(), is_extension_supported);
}
