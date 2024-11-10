#include "DrawableObject.h"

DrawableObject::DrawableObject(ShaderProgram* shader, const std::string& type) : shader(shader), modelMatrix(1.0f), type(type) {}

void DrawableObject::translate(glm::vec3& translation) {
    transformationApply.AddTransformation(new TransformationTranslate(translation));
    modelMatrix = glm::translate(modelMatrix, translation);
}

void DrawableObject::rotate(float angle, glm::vec3& axis) {
    transformationApply.AddTransformation(new TransformationRotate(angle, axis));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void DrawableObject::scale(glm::vec3& scaling) {
    transformationApply.AddTransformation(new TransformationScale(scaling));
    modelMatrix = glm::scale(modelMatrix, scaling);
}

void DrawableObject::applyTransformations(ShaderProgram* shaderProgram) const {
    shaderProgram->setMat4("modelMatrix", modelMatrix);
}

void DrawableObject::randomTranslate(float maxTranslation)
{
    float x = (rand() % (int)(2 * maxTranslation * 100)) / 100.0f - maxTranslation;
    float y = 0;
    float z = (rand() % (int)(2 * maxTranslation * 100)) / 100.0f - maxTranslation;

    glm::vec3 translation(x, y, z);
    transformationApply.AddTransformation(new TransformationTranslate(translation));
    modelMatrix = glm::translate(modelMatrix, translation);
}
