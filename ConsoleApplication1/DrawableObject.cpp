#include "DrawableObject.h"

DrawableObject::DrawableObject(ShaderProgram* shader) : shader(shader) {}

void DrawableObject::translate( glm::vec3& translation) {
    transformation.translate(translation);
}

void DrawableObject::rotate(float angle,  glm::vec3& axis) {
    transformation.rotate(angle, axis);
}

void DrawableObject::scale( glm::vec3& scaling) {
    transformation.scale(scaling);
}
