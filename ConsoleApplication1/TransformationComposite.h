#pragma once
#include "Transformation.h"

class TransformationComposite : public Transformation

{
public:
	void addTransformation(Transformation* transformation);
	glm::mat4 apply(glm::mat4 modelMatrix) override;
private:
	std::vector<Transformation*> transformations;
};

