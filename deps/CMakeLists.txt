# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw EXCLUDE_FROM_ALL)

# glad
add_subdirectory(glad)

# stb
include_directories(stb)

# glm
include_directories(deps/glm)