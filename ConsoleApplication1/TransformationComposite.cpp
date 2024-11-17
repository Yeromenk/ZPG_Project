#include "TransformationComposite.h"

void TransformationComposite::addTransformation(Transformation* transformation)
{
	transformations.push_back(transformation);
}

glm::mat4 TransformationComposite::apply()
{
	glm::mat4 result = glm::mat4(1.0f);
	for (auto transformation : transformations)
	{
		result = transformation->apply() * result;
	}
	return result;
}