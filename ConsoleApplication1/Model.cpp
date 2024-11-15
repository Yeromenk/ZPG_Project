#include "Model.h"

Model::Model(ShaderProgram* shaderProgram, const float* points, int arraySize, int vertexCount, GLenum drawMode, const std::string& type)
    : DrawableObject(shaderProgram, type), drawMode(drawMode), vertexCount(vertexCount) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, arraySize, points, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    shader->use();
    shader->setMat4("model", modelMatrix);
    shader->setMat4("viewMatrix", viewMatrix);
    shader->setMat4("projectionMatrix", projectionMatrix);
    applyTransformations(shader);

    glBindVertexArray(VAO);
    glDrawArrays(drawMode, 0, vertexCount);
    glBindVertexArray(0);

	glUseProgram(0);
}

