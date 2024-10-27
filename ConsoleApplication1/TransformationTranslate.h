#pragma once
#include "Transformation.h"

class TransformationTranslate : public Transformation
{
public:
	TransformationTranslate(glm::vec3& translation);
	glm::mat4 apply();
};

