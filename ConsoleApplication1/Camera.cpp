#include "Camera.h"


Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ)
    : position(glm::vec3(posX, posY, posZ)), up(glm::vec3(upX, upY, upZ)), yaw(-90.0f), pitch(0.0f), speed(2.5f) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::setProjectionMatrix(const glm::mat4& projection)
{
	projectionMatrix = projection;
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    updateCameraVectors();
    notify("camera");
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
}

void Camera::move_forward(float deltaTime) {
    position += front * speed * deltaTime;
	notify("camera");
}

void Camera::move_backward(float deltaTime) {
    position -= front * speed * deltaTime;
    notify("camera");
}

void Camera::move_left(float deltaTime) {
    position -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;
    notify("camera");
}

void Camera::move_right(float deltaTime) {
    position += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
    notify("camera");
}

glm::vec3 Camera::getPosition() const {
	return position;
}

glm::vec3 Camera::getDirection() const {
	return front;
}