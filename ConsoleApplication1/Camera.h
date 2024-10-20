#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader; // Forward declaration

class Camera {
public:
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void processMouseMovement(float xoffset, float yoffset);
	void processKeyboardInput(int key, float deltaTime);
    void move_forward(float deltaTime);
	void move_backward(float deltaTime);
	void move_left(float deltaTime);
	void move_right(float deltaTime);

private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;
    float yaw;
    float pitch;
    float speed;
    void updateCameraVectors();
};

#endif // CAMERA_H
