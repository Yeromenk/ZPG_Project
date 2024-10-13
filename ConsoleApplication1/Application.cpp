#include "Application.h"
#include <iostream>

int Application::current_scene = 0;

std::vector<glm::mat4> treeTransforms;
Model* treeModel;

// Constructor
Application::Application() {
	if (!glfwInit()) {
		std::cerr << "ERROR: could not start GLFW3\n";
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
}

// Destructor
Application::~Application() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

// Initialization
void Application::initialization() {
	glfwSetErrorCallback(errorCallbacks);
	glfwSetKeyCallback(window, keyCallbacks);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);

	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

}

// Create shaders
void Application::createShaders() {
	triangleShader = new Shader();
	quadShader = new Shader();

	triangleShader->createShaderPrograms(false);
	quadShader->createShaderPrograms(true);
}

// Create models
void Application::createModels() {
	model = new Model();
	model->createTriangle();
	model->createRectangle();

	treeModel = new Model();
	treeModel->createTree();
}

void Application::createTrees(int numTrees)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> posDist(-5.0f, 5.0f);
	std::uniform_real_distribution<float> scaleDist(0.5f, 2.0f);
	std::uniform_real_distribution<float> rotDist(0.0f, glm::two_pi<float>());

	for (int i = 0; i < numTrees; ++i) {
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(posDist(gen), 0.0f, posDist(gen)));
		transform = glm::rotate(transform, rotDist(gen), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::scale(transform, glm::vec3(scaleDist(gen)));
		treeTransforms.push_back(transform);
	}
}

// Run application
void Application::run() {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		if (current_scene == 0)
		{
			// triangle
			triangleShader->use();

			glm::mat4 M1 = glm::mat4(1.0f);
			M1 = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			M1 = glm::translate(M1, glm::vec3(-0.5f, 0.0f, 0.0f));

			GLint idModelTransform = glGetUniformLocation(triangleShader->getProgramID(), "modelMatrix");
			glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M1[0][0]);

			model->renderTriangle();

			// quad
			quadShader->use();

			glm::mat4 M2 = glm::mat4(1.0f);
			M2 = glm::translate(M2, glm::vec3(0.5f, 0.0f, 0.0f));

			idModelTransform = glGetUniformLocation(quadShader->getProgramID(), "modelMatrix");
			glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M2[0][0]);

			model->renderRectangle();


		}
		else if (current_scene == 1)
		{
			quadShader->use();
			GLint idModelTransform = glGetUniformLocation(quadShader->getProgramID(), "modelMatrix");

			for (const auto& transform : treeTransforms) {
				glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &transform[0][0]);
				treeModel->renderTree();
			}
		}


		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

// Callbacks
void Application::errorCallbacks(int error, const char* description) {
	fputs(description, stderr);
}

void Application::keyCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		current_scene = 0;
		printf("Scene 1\n");
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		current_scene = 1;
		printf("Scene 2\n");
	}
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}