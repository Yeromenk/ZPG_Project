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
#include <glm/gtc/matrix_inverse.hpp>
#include "Light.h"
#include "Model.h"


class Application {
public:
    Application();
    ~Application();

    void run();
    void mainLoop();
    void processInput(GLFWwindow* window);
    void updateProjectionMatrix(int width, int height);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void handleMouseClick();
	void addTreeAtPosition(glm::vec3& position);

    int generateUniqueID();
	DrawableObject* getObjectByID(int id);

private:
    GLFWwindow* window;
    Scene* currentScene;
    Scene* primitiveScene;
    Scene* forestScene;
    Scene* sphereScene;
    Scene* lightScene;
    Scene* nightForestScene;
    Camera* camera;
    CameraController* cameraController;
    std::vector<DrawableObject*> allObjects;

	ShaderProgram* phongTextureShader;
	Material* treeMaterial;
	Texture* treeTexture;

    int currentId;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif 