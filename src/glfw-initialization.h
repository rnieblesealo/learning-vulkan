#pragma once // Prevent including this multiple times in same translation unit; non-standard

namespace veng
{
struct GlfwInitialization
{
  public:
    GlfwInitialization();
    ~GlfwInitialization();

    GlfwInitialization(const GlfwInitialization &)            = delete; // No copy
    GlfwInitialization &operator=(const GlfwInitialization &) = delete; // No copy assignment
};
} // namespace veng
