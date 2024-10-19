#include "Transformation.h"


Transformation::Transformation() : modelMatrix(glm::mat4(1.0f))
{
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::translate( glm::vec3& translation) {
    modelMatrix = glm::translate(modelMatrix, translation);
}

void Transformation::rotate(float angle,  glm::vec3& axis) {
    float rotate = glm::radians(angle);
    modelMatrix = glm::rotate(modelMatrix, rotate, axis);
}

void Transformation::scale( glm::vec3& scale) {
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Transformation::apply(ShaderProgram* shader) const {
    GLint modelLoc = shader->getUniformLocation("modelMatrix");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

}