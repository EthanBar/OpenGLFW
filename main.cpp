#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to fix compilation on OS X
#endif

    // Create window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, World!", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Verify GLAD initialized
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport size and callback for window resize
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    Shader shader("shaders/basic.vsh", "shaders/basic.fsh");


    float vertices[] = {
            0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 1.0f, // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
            -0.5f,  0.5f, 0.0f, 0.5f, 0.2f, 0.8f, // top left
            0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3,   // second Triangle
            3, 4, 0
    };

    Model model;
    model.setBuffer(vertices, sizeof(vertices));
    model.setIndices(indices, sizeof(indices));
    model.setAttribute(0, 3, GL_FLOAT, 6 * sizeof(float), nullptr);
    model.setAttribute(1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));


    // uncomment this call to draw in wireframe polygons.
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int framebufferWidth, framebufferHeight;

    // Fix for retina display
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);



    // Main loop
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Prepare to render
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shader.use();
        glBindVertexArray(model.vao);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
//        glDrawArrays(GL_TRIANGLES, 0, 4);

        // Check and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    model.cleanUp();
    glfwTerminate();

    return 0;
}
