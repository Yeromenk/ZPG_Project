#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include "Scene.h"
#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    void initWindow();
    void mainLoop();
    void processInput(GLFWwindow* window);

    GLFWwindow* window;
    Scene* currentScene;
    Scene* primitiveScene;
    Scene* forestScene;

};

#endif // APPLICATION_H
