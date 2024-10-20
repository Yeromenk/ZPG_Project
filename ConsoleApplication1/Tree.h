#pragma once

#include <GL/glew.h>
#include "DrawableObject.h"
#include "Models/tree.h"


class Tree : public DrawableObject {
public:
    Tree(ShaderProgram* shader);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    Transformation transformation;

private:
    GLuint vbo;
    GLuint vao;
};
