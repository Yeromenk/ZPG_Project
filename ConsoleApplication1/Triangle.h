// Triangle.h
#pragma once
#include "DrawableObject.h"
#include "Transformation.h"

class Triangle : public DrawableObject {
public:
    Triangle(ShaderProgram* shader, float* vertices, size_t size);
    void draw() override;
    Transformation transformation; // Add transformation member

private:
    GLuint vao, vbo;
};
