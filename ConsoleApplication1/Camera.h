#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Subject.h"

class Shader; 

class Camera : public Subject{
public:
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void processMouseMovement(float xoffset, float yoffset);
	void setProjectionMatrix(const glm::mat4& projection);
    void move_forward(float deltaTime);
	void move_backward(float deltaTime);
	void move_left(float deltaTime);
	void move_right(float deltaTime);

    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;

private:
    glm::vec3 position;
	glm::mat4 projectionMatrix;
    glm::vec3 up;
    glm::vec3 front;
    float yaw;
    float pitch;
    float speed;

    void updateCameraVectors();
};

#endif 
