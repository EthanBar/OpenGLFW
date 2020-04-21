#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "data.h"
#include "shader.h"
#include "model.h"
#include "texture.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello, World!", nullptr, nullptr);
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shader("shaders/basic.vsh", "shaders/basic.fsh");


//    Model model;
//    model.setBuffer(vertices, sizeof(vertices));
//    model.setIndices(indices, sizeof(indices));
//    model.setAttribute(0, 3, GL_FLOAT, 8 * sizeof(float), nullptr);
//    model.setAttribute(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    model.setAttribute(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    Model model;
    model.setBuffer(cubeVertices, sizeof(cubeVertices));
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


    shader.use();
    shader.setInt("text1", 0);
    shader.setInt("text2", 1);


    // Main loop
    while(!glfwWindowShouldClose(window)) {

        // Time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Prepare to render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        text1.use();
        text2.use();
        model.use();

        shader.setFloat("time", currentFrame);

        // pass projection matrix to shader
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);

        // Render

        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 mdl = glm::mat4(1.0f);
            mdl = glm::translate(mdl, cubePositions[i]);
            float angle = 20.0f * (float)i + 10.0f;
            mdl = glm::rotate(mdl, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", mdl);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

// process all keyboard input
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// window size change callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


// mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// scroll wheel callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}