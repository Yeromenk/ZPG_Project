#include "CameraController.h"

CameraController::CameraController(Camera* camera) : camera(camera) {}

void CameraController::processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->move_forward(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->move_backward(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->move_left(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->move_right(deltaTime);
    }
}

void CameraController::processMouseMovement(float xoffset, float yoffset) {
    camera->processMouseMovement(xoffset, yoffset);
}
