#ifndef APPLICATION_H
#define APPLICATION_H
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>
#include "Scene.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include <iostream>
#include <random>


class Application {
public:
    Application();
    ~Application();
    void run();

private:
  //  void initWindow();
    void mainLoop();
    void processInput(GLFWwindow* window);

    GLFWwindow* window;
    Scene* currentScene;
    Scene* primitiveScene;
    Scene* forestScene;
	Camera* camera;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

#endif // APPLICATION_H