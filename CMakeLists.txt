cmake_minimum_required(VERSION 3.15)
project(Raytracer)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SRC src/*.cpp)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_subdirectory(deps)

target_include_directories(${PROJECT_NAME} PRIVATE include deps/stb)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw glm::glm)