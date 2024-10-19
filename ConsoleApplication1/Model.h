#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include <vector>

class Model : public DrawableObject {
public:
    Model(ShaderProgram* shader);
    ~Model();

    void load(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    void draw();

private:
    GLuint vao, vbo, ebo;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

#endif // MODEL_H
