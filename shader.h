#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // Assigned ID
    unsigned int ID;

    // Generates shaders from file path
    Shader(const char* vertexPath, const char* fragmentPath);

    // Activate the shader
    void use();

    // Uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    // Utility function for checking shader compilation/linking errors.
    static void checkCompileErrors(unsigned int shader, const std::string& type);
};
#endif