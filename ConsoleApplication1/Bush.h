#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "DrawableObject.h"
#include "Models/bushes.h"



class Bush : public DrawableObject {
public:
    Bush(ShaderProgram* shader);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    Transformation transformation;

private:
    GLuint vbo;
    GLuint vao;
};
