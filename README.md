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

### Language Stuff
- Forward declarations avoid:
    - Circular deps (Header A includes header B, and header B also includes header A)
        - These can lead to compilation errors; avoid them completely!
- Use forward declarations any time you don't need the complete type def, as a general rule
- `const` on function declaration:
    - Can call on const instances of class
    - Function promises not to modify class member variables
- Compiler needs full type definition to create a reference
> i.e. If we try to pass something as a const &, we need to `#include` it first...

### GSL
Some examples:

```cpp
gsl::zstring zString; // A zero-terminated string
gsl::span<gsl::zstring> span; // View over contiguous object sequence

span.begin(); // Span supports iterator use
span.end();

gsl::not_null notNull; // Pointer that can't be null; crashes program if it is
```

## Vulkan

- Inverted Y coord system (+X towards right, +Y towards bottom)
- **Monitor Logical Pos:**
```txt
[1][2]

If monitor 1's lower right has pos (1920, 1080), then monitor 2's top left is (1920, 0)
```
- The monitor "work area" refers to the desktop's area minus taskbar, menu bar, etc.
