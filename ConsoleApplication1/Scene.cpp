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

void Scene::draw() {
    for (auto object : objects) {
        object->draw();
    }
}
