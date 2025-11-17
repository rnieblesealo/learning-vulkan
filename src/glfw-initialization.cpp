#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>

#include "glfw-initialization.h"

namespace veng
{
GlfwInitialization::GlfwInitialization()
{
  if (glfwInit() != GLFW_TRUE)
  {
    std::exit(EXIT_FAILURE);
  }
}

GlfwInitialization::~GlfwInitialization() { glfwTerminate(); }
} // namespace veng