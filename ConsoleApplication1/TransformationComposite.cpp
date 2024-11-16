#include "TransformationComposite.h"

void TransformationComposite::addTransformation(Transformation* transformation)
{
	transformations.push_back(transformation);
}

glm::mat4 TransformationComposite::apply(glm::mat4 modelMatrix)
{
	for (auto transformation : transformations)
	{
		modelMatrix = transformation->apply(modelMatrix);
	}
	return modelMatrix;
}