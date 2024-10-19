// Triangle.cpp
#include "Triangle.h"

Triangle::Triangle(ShaderProgram* shader, float* vertices, size_t size) : DrawableObject(shader) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::draw() {
    shader->use();
    transformation.apply(shader); // Apply transformation

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Adjust the number of vertices as needed
    glBindVertexArray(0);
}
