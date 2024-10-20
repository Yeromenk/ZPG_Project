#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
    for (auto object : objects) {
        delete object;
    }
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    for (auto& object : objects) {
        object->draw(viewMatrix, projectionMatrix);
    }
}

