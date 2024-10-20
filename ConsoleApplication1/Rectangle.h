#pragma once

#include <GL/glew.h>
#include "DrawableObject.h"


class Rectangle : public DrawableObject {
public:
    Rectangle(ShaderProgram* shader, float* vertices, size_t size);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    Transformation transformation;

private:
    GLuint vbo;
    GLuint vao;
};
