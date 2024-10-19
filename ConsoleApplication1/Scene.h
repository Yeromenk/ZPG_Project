#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include "DrawableObject.h"
#include <vector>
#include <tuple>

class Scene {
public:
    Scene();
    ~Scene();

    void addObject(DrawableObject* object);
    void draw();

private:
    std::vector<DrawableObject*> objects;
};

#endif // SCENE_H
