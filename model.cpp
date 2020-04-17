#include <glad/glad.h>
#include <iostream>

#include "model.h"

Model::Model() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void Model::setBuffer(const void* data, GLsizeiptr size) {
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Model::setIndices(const void* data, GLsizeiptr size) {
    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Model::setAttribute(int position, int size, GLenum type, GLsizei stride, const void* offset) {
    glBindVertexArray(vao);

    glVertexAttribPointer(position, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(position);
}

void Model::cleanUp() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

}

