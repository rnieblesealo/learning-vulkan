# Notes

These are my notes I took while following along!

## Installing Vulkan
[Install SDK](https://vulkan.lunarg.com/sdk/home#mac)
- `vulkaninfo --html` to generate report file

### Required Deps
- [GLFW](https://github.com/glfw/glfw): High-level graphics API
- [GLM](https://github.com/g-truc/glm): Graphics math 
- [GSL](https://github.com/microsoft/GSL): Wraps C++ stuff into more readable/robust definitions 

## CMake Stuff 

### Building w/Ninja
- `cmake .. -G Ninja` instead of `cmake ..` to generate `build.ninja` file and build with Ninja
    - `ninja` instead of `make`

### Adding GH Dependencies w/FetchContent 
1. `FetchContent_Declare()`
2. Make available
3. Link

> See `CMakeLists.txt` and how it adds GLFW/GLM/GSL

## C++

### GSL
Some examples:

```cpp
gsl::zstring zString; // A zero-terminated string
gsl::span<gsl::zstring> span; // View over contiguous object sequence

span.begin(); // Span supports iterator use
span.end();

gsl::not_null notNull; // Pointer that can't be null; crashes program if it is

```