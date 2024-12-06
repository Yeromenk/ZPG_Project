#ifndef MODEL_H
#define MODEL_H

#include "DrawableObject.h"
#include <random>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "Material.h"
#include "Texture.h"

class Model : public DrawableObject {
public:
    Model(ShaderProgram* shaderProgram, const float* points, int arraySize, int vertexCount, GLenum drawMode, const std::string& type, Material* material,  int id, Texture* texture = nullptr);

    Model(const char* path, ShaderProgram* shaderProgram, Material* material, Texture* texture, const std::string& type, int id);
    ~Model();

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    int getID() const override;

private:
    GLuint VAO, VBO;
    GLenum drawMode;
    int vertexCount;
    int id;
    Material* material;
    Texture* texture;
};

#endif