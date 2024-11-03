#include "Application.h"


float triangleVertices[] = {
	-0.3f,  0.8f, 0.0f,  0.3f,  0.5f, 0.0f,
	-0.4f, 0.5f, 0.0f,  0.3f, 0.5f, 0.0f,
	0.1f, 0.6f, 0.0f, 0.9f, 0.5f, 0.0f
};

Application::Application() : window(nullptr), currentScene(nullptr), primitiveScene(nullptr), forestScene(nullptr), camera(nullptr), sphereScene(nullptr), lightScene(nullptr) {
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

	glEnable(GL_DEPTH_TEST);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	camera = new Camera(0.0f, 2.0f, 3.0f, 0.0f, 0.5f, 0.0f);
	cameraController = new CameraController(camera);

	primitiveScene = new Scene();
	forestScene = new Scene();
	sphereScene = new Scene();
	lightScene = new Scene();

	Light* light = new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	sphereScene->setLight(light);
	lightScene->setLight(light);
	
	ShaderProgram* shader1 = new ShaderProgram(camera, light);
	shader1->create("./Shaders/vertex_shader.glsl", "./Shaders/fragment_shader.glsl");

	// different shaders
	ShaderProgram* shaderPhong = new ShaderProgram(camera, light);
	shaderPhong->create("./Shaders/phong_vertex_shader.glsl", "./Shaders/phong_fragment_shader.glsl");
	ShaderProgram* constantShader = new ShaderProgram(camera, light);
	constantShader->create("./Shaders/constant_vertex_shader.glsl", "./Shaders/constant_fragment_shader.glsl");
	ShaderProgram* lambertShader = new ShaderProgram(camera, light);
	lambertShader->create("./Shaders/lambert_vertex_shader.glsl", "./Shaders/lambert_fragment_shader.glsl");
	ShaderProgram* blinnShader = new ShaderProgram(camera, light);
	blinnShader->create("./Shaders/blinn_vertex_shader.glsl", "./Shaders/blinn_fragment_shader.glsl");

	Model* triangleModel = new Model(shader1, triangleVertices, sizeof(triangleVertices), 3, GL_TRIANGLES);
	Model* plainModel = new Model(shader1, plain, sizeof(plain), 6, GL_TRIANGLES);

	glm::vec3 treePosition = glm::vec3(0.0f, 0.0f, -2.0f);
	glm::vec3 treeSize = glm::vec3(2.0f);

	triangleModel->translate(treePosition);
	triangleModel->scale(treeSize);

	primitiveScene->addObject(triangleModel);

	forestScene->addObject(plainModel);

	glm::vec3 spherePositions[] = {
		glm::vec3(-1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(1.0f, 0.0f, -1.0f)
	};

	glm::vec3 sphereScale = glm::vec3(0.5f);

	// 3 scene
	for (int i = 0; i < 4; i++) {
		Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES);
		sphereModel->translate(spherePositions[i]);
		sphereModel->scale(sphereScale);
		sphereScene->addObject(sphereModel);
	}

	// 4 scene
	for (int i = 0; i < 4; i++) {
		if (i == 0)
		{
			Model* giftModel = new Model(constantShader, gift, sizeof(gift), 66624, GL_TRIANGLES);
			giftModel->translate(spherePositions[i]);
			giftModel->scale(sphereScale);
			lightScene->addObject(giftModel);
		}
		else if (i == 1)
		{
			Model* suziFlatModel = new Model(lambertShader, suziFlat, sizeof(suziFlat), 2904, GL_TRIANGLES);
			suziFlatModel->translate(spherePositions[i]);
			suziFlatModel->scale(sphereScale);
			lightScene->addObject(suziFlatModel);
		}
		else if (i == 2)
		{
			Model* suziSmoothModel = new Model(blinnShader, suziSmooth, sizeof(suziSmooth), 2904, GL_TRIANGLES);
			suziSmoothModel->translate(spherePositions[i]);
			suziSmoothModel->scale(sphereScale);
			lightScene->addObject(suziSmoothModel);
		}
		else if (i == 3)
		{
			Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES);
			sphereModel->translate(spherePositions[i]);
			sphereModel->scale(sphereScale);
			lightScene->addObject(sphereModel);
		}
	}

	for (int i = 0; i < 50; i++) {
		Model* treeModel = new Model(shader1, tree, sizeof(tree), 92814, GL_TRIANGLES);

		// Random x position between -1.0 and 1.0
		float randomX = (float)(rand() % 200) / 100.0f - 1.0f;

		// Ground level y position
		float groundY = 0.0f;

		// Random z position between -1.0 and 1.0
		float randomZ = (float)(rand() % 200) / 100.0f - 1.0f;

		glm::vec3 treePosition = glm::vec3(randomX, groundY, randomZ);
		glm::vec3 treeScale = glm::vec3(0.03f + (float)(rand() % 10) / 100.0f);
		glm::vec3 treeRotate = glm::vec3(0.f, 0.8f, 0.f);
		float randomRotation = static_cast<float>(rand() % 360);

		treeModel->translate(treePosition);
		treeModel->scale(treeScale);
		treeModel->rotate(randomRotation, treeRotate);
		forestScene->addObject(treeModel);
	}

	for (int i = 0; i < 50; i++) {
		Model* bushModel = new Model(shader1, bushes, sizeof(bushes), 92814, GL_TRIANGLES);

		// Random x position between -1.0 and 1.0
		float randomX = (float)(rand() % 200) / 100.0f - 1.0f;

		// Ground level y position
		float groundY = 0.0f;

		// Random z position between -1.0 and 1.0
		float randomZ = (float)(rand() % 200) / 100.0f - 1.0f;

		glm::vec3 treePosition = glm::vec3(randomX, groundY, randomZ);
		glm::vec3 treeScale = glm::vec3(0.03f + (float)(rand() % 10) / 100.0f);
		glm::vec3 treeRotate = glm::vec3(0.f, 0.8f, 0.f);
		float randomRotation = static_cast<float>(rand() % 360);

		bushModel->translate(treePosition);
		bushModel->scale(treeScale);
		bushModel->rotate(randomRotation, treeRotate);
		forestScene->addObject(bushModel);
	}

	currentScene = primitiveScene;
}

Application::~Application() {
	delete camera;
	delete cameraController;
	delete primitiveScene;
	delete forestScene;
	delete sphereScene;
	delete lightScene;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::run() {
	mainLoop();
}

void Application::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Capture mouse movement
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		static double lastX = xpos, lastY = ypos;
		float xoffset = static_cast<float>(xpos - lastX);
		float yoffset = static_cast<float>(lastY - ypos);
		lastX = xpos;
		lastY = ypos;

		cameraController->processMouseMovement(xoffset, yoffset);
		currentScene->draw(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::processInput(GLFWwindow* glfwWindow) {
	static float lastFrame = 0.0f;
	float currentFrame = static_cast<float>(glfwGetTime());
	float deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(glfwWindow, true);

	if (glfwGetKey(glfwWindow, GLFW_KEY_1) == GLFW_PRESS) {
		currentScene = primitiveScene;
		std::cout << "Scene 1" << std::endl;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_2) == GLFW_PRESS) {
		currentScene = forestScene;
		std::cout << "Scene 2" << std::endl;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_3) == GLFW_PRESS) {
		currentScene = sphereScene;
		std::cout << "Scene 3" << std::endl;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_4) == GLFW_PRESS) {
		currentScene = lightScene;
		std::cout << "Scene 4" << std::endl;
	}

	cameraController->processInput(glfwWindow, deltaTime);
}
