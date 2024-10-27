#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "DrawableObject.h"
#include "ShaderProgram.h"

class Model : public DrawableObject {
private:
    GLuint VBO;
    GLuint VAO;
    int drawMode;
    int vertexCount;
    DrawableObject* object;

public:
    Model(ShaderProgram* shaderProgram, const float* points, int arraySize, int vertexCount, GLenum drawMode);

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
};