#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(float angle, glm::vec3& axis)
{
	float radians = glm::radians(angle);
	modelMatrix = glm::rotate(glm::mat4(1.0), radians ,axis);
}

glm::mat4 TransformationRotate::apply()
{
	return modelMatrix;
}