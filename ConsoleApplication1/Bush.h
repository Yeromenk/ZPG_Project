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
    void draw() override;

private:
    GLuint vbo;
    GLuint vao;
};
