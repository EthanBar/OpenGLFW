#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

class Model {
public:
    unsigned int vao{}, vbo{}, ebo{};
    Model();
    void setIndices(const void* data, GLsizeiptr size);
    void setBuffer(const void* data, GLsizeiptr size);
    void setAttribute(int position, int size, GLenum type, GLsizei stride, const void* offset);
    void cleanUp();
};

#endif
