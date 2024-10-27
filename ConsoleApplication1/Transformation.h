#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"


class Transformation {
public:
    glm::mat4 modelMatrix;
    Transformation();
};

#endif 