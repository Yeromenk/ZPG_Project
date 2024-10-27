#include "TransformationScale.h"

TransformationScale::TransformationScale(glm::vec3& scale)
{
	modelMatrix = glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 TransformationScale::apply()
{
	return modelMatrix;
}