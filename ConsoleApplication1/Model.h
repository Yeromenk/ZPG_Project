#ifndef MODEL_H
#define MODEL_H

#include "DrawableObject.h"
#include <random>

#include "Material.h"

class Model : public DrawableObject {
public:
    Model(ShaderProgram* shaderProgram, const float* points, int arraySize, int vertexCount, GLenum drawMode, const std::string& type, Material* material);
    ~Model();

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    void randomTranslate(float maxTranslation);

private:
    GLuint VAO, VBO;
    GLenum drawMode;
    int vertexCount;
	Material* material;
};

#endif