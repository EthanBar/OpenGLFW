#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    glEnable(GL_DEPTH_TEST);

    Shader shader("shaders/basic.vsh", "shaders/basic.fsh");


//    float vertices[] = {
//            // positions          // colors           // texture coords
//            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
//    };
//
//    float vertexCoords[] = {  // Coordinates for the vertices of a cube.
//            1,1,1,
//            1,1,-1,
//            1,-1,-1,
//            1,-1,1,
//            -1,1,1,
//            -1,1,-1,
//            -1,-1,-1,
//            -1,-1,1
//    };
//
//    unsigned int indices[] = {
//            0, 1, 3,  // first Triangle
//            1, 2, 3   // second Triangle
//    };

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

//    Model model;
//    model.setBuffer(vertices, sizeof(vertices));
//    model.setIndices(indices, sizeof(indices));
//    model.setAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
//    model.setAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    model.setAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    Model model;
    model.setBuffer(vertices, sizeof(vertices));
    model.setAttribute(0, 3, GL_FLOAT, 5 * sizeof(float), nullptr);
    model.setAttribute(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));


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

//    glm::mat4 mdl = glm::mat4(1.0f);
//    mdl = glm::rotate(mdl, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int modelLoc = glGetUniformLocation(shader.ID, "model");
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    int projLoc = glGetUniformLocation(shader.ID, "projection");
    // Main loop
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Prepare to render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render
        shader.use();
        count += 0.016666f;
        shader.setFloat("time", count);
        text1.use();
        text2.use();

        model.use();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 mdl = glm::mat4(1.0f);
            mdl = glm::translate(mdl, cubePositions[i]);
            float angle = 20.0f * (float)i + 10.0f;
            mdl = glm::rotate(mdl, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mdl));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

//        mdl = glm::rotate(mdl, 0.01f * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));



        model.use();

//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        // Check and call events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    model.cleanUp();
    glfwTerminate();

    return 0;
}
