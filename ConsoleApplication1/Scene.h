#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "DrawableObject.h"
#include <glm/glm.hpp>

#include "Light.h"

class Scene {
public:
    Scene();
    ~Scene();

    void addObject(DrawableObject* object);
    void draw(Camera* camera);
    void setLight(Light* light);
    void rotateTrees();
	void translateBushes(float maxTranslation);

private:
    std::vector<DrawableObject*> objects;
	std::vector<DrawableObject*> rotatingTrees;
	std::vector<DrawableObject*> randomBushes;
	Light* light;
};

#endif 