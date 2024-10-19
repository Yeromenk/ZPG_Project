#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject {
public:
    DrawableObject(ShaderProgram* shader);
    virtual ~DrawableObject() = default;

    void translate( glm::vec3& translation);
    void rotate(float angle,  glm::vec3& axis);
    void scale( glm::vec3& scaling);

    virtual void draw() = 0;

protected:

    ShaderProgram* shader;
    Transformation transformation;
};

#endif // DRAWABLEOBJECT_H
