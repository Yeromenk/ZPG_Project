#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "DrawableObject.h"
#include <glm/glm.hpp>

class Scene {
public:
    Scene();
    ~Scene();

    void addObject(DrawableObject* object);
   // void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void draw(Camera* camera);

private:
    std::vector<DrawableObject*> objects;
};

#endif // SCENE_H