#pragma once
#include "Transformation.h"

class TransformationComposite : public Transformation
{
public:
	void addTransformation(Transformation* transformation);

	glm::mat4 apply() override;

private:
	std::vector<Transformation*> transformations;
};


