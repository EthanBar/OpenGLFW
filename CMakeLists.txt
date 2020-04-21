cmake_minimum_required(VERSION 3.15)
project(OpenGLFW)
set(CMAKE_CXX_STANDARD 14)
add_executable(OpenGLFW main.cpp shader.h shader.cpp model.cpp model.h stb_image.h texture.cpp texture.h camera.h data.h)
add_subdirectory(glm)
target_link_libraries(${PROJECT_NAME} glm)

set (source "${CMAKE_SOURCE_DIR}/shaders")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/shaders")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

set (source "${CMAKE_SOURCE_DIR}/textures")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/textures")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

add_subdirectory(glad/)
target_link_libraries(${PROJECT_NAME} glad)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)