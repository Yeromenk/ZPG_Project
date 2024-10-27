#pragma once
#include "Transformation.h"
#include <vector>

class TransformationApply : public Transformation
{
private:
	std::vector<Transformation*> transformations;

public:
	void AddTransformation(Transformation* transformation);

};

