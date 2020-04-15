cmake_minimum_required(VERSION 3.15)
project(OpenGLFW)
set(CMAKE_CXX_STANDARD 14)

add_executable(OpenGLFW main.cpp shader.h)

add_subdirectory(glad/)
target_link_libraries(${PROJECT_NAME} glad)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)


find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)