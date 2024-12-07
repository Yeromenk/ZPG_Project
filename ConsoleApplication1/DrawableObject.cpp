#include "DrawableObject.h"


DrawableObject::DrawableObject(ShaderProgram* shader, const std::string& type) : shader(shader), modelMatrix(1.0f), type(type)
{
    transformationApply = new TransformationComposite();
}

DrawableObject::~DrawableObject()
{
	delete transformationApply;
}

void DrawableObject::translate(glm::vec3& translation) {
    transformationApply->addTransformation(new TransformationTranslate(translation));
    modelMatrix = glm::translate(modelMatrix, translation);
}

void DrawableObject::rotate(float angle, glm::vec3& axis) {
    transformationApply->addTransformation(new TransformationRotate(angle, axis));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void DrawableObject::scale(glm::vec3& scaling) {
    transformationApply->addTransformation(new TransformationScale(scaling));
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
    transformationApply->addTransformation(new TransformationTranslate(translation));
    modelMatrix = glm::translate(modelMatrix, translation);
}

ShaderProgram* DrawableObject::getShaderProgram() const
{
	return shader;
}

glm::mat4 DrawableObject::getModelMatrix() const
{
	return modelMatrix;
}

std::string DrawableObject::getType() const
{
	return type;
}