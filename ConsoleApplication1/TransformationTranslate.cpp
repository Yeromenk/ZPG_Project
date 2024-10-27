#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(glm::vec3& translation)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), translation);
}

glm::mat4 TransformationTranslate::apply()
{
	return modelMatrix;
}