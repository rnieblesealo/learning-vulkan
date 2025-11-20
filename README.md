# Notes

These are my notes I took while following along!

If you see swearing (unprofessional) just know it helps me cope with the dread that most surely inspired it :D

## Installing Vulkan
[Install SDK](https://vulkan.lunarg.com/sdk/home#mac)
- `vulkaninfo --html` to generate report file

### Required Deps
- [GLFW](https://github.com/glfw/glfw): High-level graphics API
- [GLM](https://github.com/g-truc/glm): Graphics math 
- [GSL](https://github.com/microsoft/GSL): Wraps C++ stuff into more readable/robust definitions 

## CMake

### Building w/Ninja
- `cmake .. -G Ninja` instead of `cmake ..` to generate `build.ninja` file and build with Ninja
    - `ninja` instead of `make`
> I think just using the VS Code extension's default `Configure` task does this for me, though!

### Adding Dependencies w/`FetchContent`
1. `FetchContent_Declare()`
2. Make available
3. Link

> See `CMakeLists.txt` and how it adds GLFW/GLM/GSL

## C++

### Language Stuff
- Forward declarations avoid:
    - Circular Deps (Header A includes header B, and header B also includes header A)
        - These can lead to compilation errors; avoid them completely!
- Use forward declarations any time you don't need the complete type def, as a general rule
- `const` on function declaration:
    - Can call on const instances of class
    - Function promises not to modify class member variables
- Compiler needs full type definition to create a reference
> i.e. If we try to pass something as a const &, we need to `#include` it first...
- It's good practice to add precompiled headerfile to all `.cpp`
    - If we try to compile on other platform and something fails, we know where to look!
- Brace-initializing with empty braces `= {}` zeroes out all members of struct/class
- You can turn a `char**` to a vector of strings like this:
```cpp
char    **string_arr    = ...;
size_t  string_arr_len  = ...;
std::vector<std::string>(string_arr, string_arr + string_arr_len);
```
> If you get confused remember a `char**` just points to a `char*` and go from there :) 

### The `Graphics::Graphics` Issue I Died With

This was an incomplete typedef; I forward-declared `Window`, which is our own thing, outside the `veng` namespace.

The fix was to `#include "glfw-window.h"`

If you ever see a bullshit include error, it's probably some forward declare or namespace fuckery!

## GSL
Some examples:

```cpp
gsl::zstring zString; // A zero-terminated string
gsl::span<gsl::zstring> span; // View over contiguous object sequence

span.begin(); // Span supports iterator use
span.end();

gsl::not_null notNull; // Pointer that can't be null; crashes program if it is
```

- `czstring` is a C-style null-terminated string

## GLFW
- By default, windows expect to be drawn to via OpenGL
    - We must tell it to not expect it via `glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API)`

## Vulkan

- Inverted Y coord system (+X towards right, +Y towards bottom)
- **Monitor Logical Pos:**
```txt
[1][2]

If monitor 1's lower right has pos (1920, 1080), then monitor 2's top left is (1920, 0)
```
- The monitor "work area" refers to the desktop's area minus taskbar, menu bar, etc.
- *Extensions** extend the base Vulkan API's capabilities

### Fixing Vulkan on macOS

Because macOS has a different graphics driver for Metal, we must use MoltenVK

MoltenVK is a translation layer that converts Vulkan calls to Metal

This requires us toI'm going to use this at my future job, so I better learn it!:
- Use a GLFW built specifically for macOS support of Vulkan:
    1. `brew install glfw`
    > `CMakeLists.txt` has been modified to find the system GLFW as opposed to the `FetchContent` built one on Apple
    2. Reconfigure and rebuild; the correct GLFW will now be used
    > `glfwVulkanSupported()` should now return `GLFW_TRUE`
- Modify the Vulkan instance creation to support MoltenVK:
    - This requires code changes; see [this GitHub issue](https://github.com/glfw/glfw/issues/1248) 

Note that as of writing this, all I was able to fix was `glfwVulkanSupported()` which now returns `GLFW_TRUE` whereas before it didn't; however, the more noteworthy issue is that `glfwGetRequiredInstanceExtensions()` still returns nothing...

**Update:** The above was due to a logic error when handling extensions. It was fixed by keeping them in an `std::vector`.

> **Side Note:** If you're struggling to do something that seems very common, put all your efforts into finding the easiest way to do it!

## VS Code

I'm going to use this at my future job, so I better learn it!

- `tasks.json` to configure command-based tasks
- To debug CMake project, do command palette and then `CMake > Debug`
