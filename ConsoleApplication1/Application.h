#ifndef APPLICATION_H
#define APPLICATION_H
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include "Scene.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include <iostream>
#include <random>
#include "ShaderLoader.h"
#include "Models/tree.h"
#include "Models/plain.h"
#include "Models/bushes.h"
#include "Models/sphere.h"
#include "Models/gift.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "CameraController.h"
#include "Light.h"
#include "Model.h"


class Application {
public:
    Application();
    ~Application();

    void run();
    void mainLoop();
    void processInput(GLFWwindow* window);

private:
    GLFWwindow* window;
    Scene* currentScene;
    Scene* primitiveScene;
    Scene* forestScene;
    Scene* sphereScene;
    Scene* lightScene;
	Camera* camera;
    CameraController* cameraController;

};

#endif 