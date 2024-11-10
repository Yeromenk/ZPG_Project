#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    for (auto object : objects) {
        delete object;
    }
}

void Scene::rotateTrees() {
	for (auto tree : rotatingTrees) {
        glm::vec3 axis(0.0f, 1.0f, 0.0f);
        tree->rotate(5.0f, axis);
	}
}

void Scene::translateBushes(float maxTranslation)
{
	for(auto bush : randomBushes)
	{
        bush->randomTranslate(maxTranslation);
	}
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
    if(object->getType() == "tree")
    {
        rotatingTrees.push_back(object);
    }
	if (object->getType() == "bush")
	{
		randomBushes.push_back(object);
	}
 }

void Scene::draw(Camera* camera) {
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix(800.0f / 600.0f);

    for (auto object : objects) {
        glm::mat4 modelMatrix = object->getModelMatrix();
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

        ShaderProgram* shader = object->getShaderProgram();
        shader->use();
        shader->setMat4("modelMatrix", modelMatrix);
        shader->setMat4("viewMatrix", viewMatrix);
        shader->setMat4("projectionMatrix", projectionMatrix);
        shader->setMat3("normalMatrix", normalMatrix);

        object->draw(viewMatrix, projectionMatrix);
    }

    if (light) {
        for (auto object : objects) {
            ShaderProgram* shader = object->getShaderProgram();
            shader->use();
            shader->setVec3("lightPosition", light->getPosition());
            shader->setVec3("lightColor", light->getColor());
            shader->setFloat("lightIntensity", light->getIntensity());
            shader->setVec3("viewPos", camera->getPosition()); 
        }
    }
}

void Scene::setLight(Light* light) {
	this->light = light;
}