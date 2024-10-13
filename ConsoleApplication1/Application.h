#ifndef APPLICATION_H
#define APPLICATION_H

#include "Shader.h"
#include "Model.h"
#include <GLFW/glfw3.h>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createModels();
	void createTrees(int numTrees);
    void run();

private:
    GLFWwindow* window;
    Shader* triangleShader;
    Shader* quadShader;
    Model* model;

    static int current_scene;

	// callbacks
    static void errorCallbacks(int error, const char* description);
	static void keyCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_focus_callback(GLFWwindow* window, int focused);
    static void window_iconify_callback(GLFWwindow* window, int iconified);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void cursor_callback(GLFWwindow* window, double x, double y);
    static void button_callback(GLFWwindow* window, int button, int action, int mode);
};


#endif 