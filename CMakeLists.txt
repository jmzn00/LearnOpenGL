set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(LearnOpenGL
    src/main.cpp
    src/Shaders/Shader.cpp
    src/Camera/Camera.cpp
    src/Material/Material.cpp
    external/glad/src/glad.c
)

target_include_directories(LearnOpenGL PRIVATE
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/glm
    ${CMAKE_SOURCE_DIR}/src/Camera
    ${CMAKE_SOURCE_DIR}/src/Shaders
    ${CMAKE_SOURCE_DIR}/src/Material
)

target_link_libraries(LearnOpenGL
    OpenGL::GL
    glfw
)
