#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationScale.h"

class DrawableObject {
public:
    DrawableObject(ShaderProgram* shader, const std::string& type);
    virtual ~DrawableObject();

    void translate(glm::vec3& translation);
    void rotate(float angle, glm::vec3& axis);
    void scale(glm::vec3& scaling);

    virtual void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
	void applyTransformations(ShaderProgram* shaderProgram) const;
	void randomTranslate(float maxTranslation);
	ShaderProgram* getShaderProgram() const { return shader; }
	glm::mat4 getModelMatrix() const { return modelMatrix; }
    std::string getType() const { return type;  }

protected:
    ShaderProgram* shader;
    TransformationComposite* transformationApply;
    glm::mat4 modelMatrix;
    std::string type;
};

#endif 