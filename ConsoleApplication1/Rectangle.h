#pragma once

#include <GL/glew.h>
#include "DrawableObject.h"


class Rectangle : public DrawableObject {
public:
    Rectangle(ShaderProgram* shader, float* vertices, size_t size);
    void draw() override;

private:
    GLuint vbo;
    GLuint vao;
};
