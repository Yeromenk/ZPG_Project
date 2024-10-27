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
#include "Triangle.h"
#include "Rectangle.h"
#include "Tree.h"
#include "Bush.h"
#include "CameraController.h"


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
	Camera* camera;
    CameraController* cameraController;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

#endif // APPLICATION_H