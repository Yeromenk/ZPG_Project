#include "TransformationApply.h"

void TransformationApply::AddTransformation(Transformation* transformation)
{
	transformations.push_back(transformation);
}