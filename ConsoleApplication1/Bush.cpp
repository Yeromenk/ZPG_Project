#include "Bush.h"

Bush::Bush(ShaderProgram* shader) : DrawableObject(shader) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bushes), bushes, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Bush::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shader->use();
    shader->setMat4("viewMatrix", viewMatrix);
    shader->setMat4("projectionMatrix", projectionMatrix);
    transformation.apply(shader);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 8730); 
    glBindVertexArray(0);
}
