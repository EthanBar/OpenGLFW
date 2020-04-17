#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"
#include "model.h"
#include "texture.h"

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
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    Model model;
    model.setBuffer(vertices, sizeof(vertices));
    model.setIndices(indices, sizeof(indices));
    model.setAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
    model.setAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    model.setAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


    // uncomment this call to draw in wireframe polygons.
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int framebufferWidth, framebufferHeight;

    // Fix for retina display
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
    Texture::init();
    Texture text1("textures/awesomeface.png", GL_TEXTURE0, GL_RGBA);
    Texture text2("textures/container.jpg", GL_TEXTURE1, GL_RGB);


    shader.use(); // don't forget to activate the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(shader.ID, "text1"), 0); // set it manually
    shader.setInt("text2", 1); // or with shader class
    float count = 0;
    // Main loop
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Prepare to render
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shader.use();
        count += 0.016666f;
        shader.setFloat("time", count);

        text1.use();
        text2.use();

        glBindVertexArray(model.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Check and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    model.cleanUp();
    glfwTerminate();

    return 0;
}
