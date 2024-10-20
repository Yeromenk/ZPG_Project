 // Triangle.h
#pragma once
#include "DrawableObject.h"
#include "Transformation.h"

class Triangle : public DrawableObject {
public:
    Triangle(ShaderProgram* shader, float* vertices, size_t size);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    Transformation transformation;

private:
    GLuint vao, vbo;
};
