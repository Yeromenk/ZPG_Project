#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class CameraController {
public:
    CameraController(Camera* camera);
    void processInput(GLFWwindow* window, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

private:
    Camera* camera;
};
