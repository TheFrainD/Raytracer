cmake_minimum_required(VERSION 3.15)
project(Raytracer)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(deps)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)