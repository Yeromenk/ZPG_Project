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

	Light* light1 = new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f);
	Light* light2 = new Light(glm::vec3(10.0f, 0.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f);
	Light* light3 = new Light(glm::vec3(-10.0f, 0.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f);
	Light* light4 = new Light(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.02f);

	std::vector<Light*> lights = { light1, light2, light3, light4 };

	forestScene->setLight(light1);
	forestScene->setLight(light2);
	forestScene->setLight(light3);
	forestScene->setLight(light4);

	sphereScene->setLight(light1);

	lightScene->setLight(light1);

	// different shaders
	ShaderProgram* shaderPhong = new ShaderProgram(camera, lights);
	shaderPhong->create("./Shaders/phong_vertex_shader.glsl", "./Shaders/phong_fragment_shader.glsl");
	ShaderProgram* constantShader = new ShaderProgram(camera, lights);
	constantShader->create("./Shaders/constant_vertex_shader.glsl", "./Shaders/constant_fragment_shader.glsl");
	ShaderProgram* lambertShader = new ShaderProgram(camera, lights);
	lambertShader->create("./Shaders/lambert_vertex_shader.glsl", "./Shaders/lambert_fragment_shader.glsl");
	ShaderProgram* blinnShader = new ShaderProgram(camera, lights);
	blinnShader->create("./Shaders/blinn_vertex_shader.glsl", "./Shaders/blinn_fragment_shader.glsl");

	Model* triangleModel = new Model(shaderPhong, triangleVertices, sizeof(triangleVertices), 3, GL_TRIANGLES, "triangle");
	Model* plainModel = new Model(shaderPhong, plain, sizeof(plain), 6, GL_TRIANGLES, "plain");

	glm::vec3 treePosition = glm::vec3(0.0f, 0.0f, -2.0f);
	glm::vec3 treeSize = glm::vec3(2.0f);

	glm::vec3 plainSize = glm::vec3(5.0f);

	triangleModel->translate(treePosition);
	triangleModel->scale(treeSize);

	primitiveScene->addObject(triangleModel);

	plainModel->scale(plainSize);
	forestScene->addObject(plainModel);

	glm::vec3 spherePositions[] = {
		glm::vec3(-1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(1.0f, 0.0f, -1.0f)
	};

	glm::vec3 modelScale = glm::vec3(0.5f);
	glm::vec3 giftScale = glm::vec3(2.0f);

	// 3 scene
	for (int i = 0; i < 4; i++) {
		Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES, "sphere");
		sphereModel->translate(spherePositions[i]);
		sphereModel->scale(modelScale);
		sphereScene->addObject(sphereModel);
	}

	// 4 scene
	for (int i = 0; i < 4; i++) {
		if (i == 0)
		{
			Model* giftModel = new Model(constantShader, gift, sizeof(gift), 66624, GL_TRIANGLES, "gift");
			giftModel->translate(spherePositions[i]);
			giftModel->scale(giftScale);
			lightScene->addObject(giftModel);
		}
		else if (i == 1)
		{
			Model* suziFlatModel = new Model(lambertShader, suziFlat, sizeof(suziFlat), 2904, GL_TRIANGLES, "suziFlat");
			suziFlatModel->translate(spherePositions[i]);
			suziFlatModel->scale(modelScale);
			lightScene->addObject(suziFlatModel);
		}
		else if (i == 2)
		{
			Model* suziSmoothModel = new Model(blinnShader, suziSmooth, sizeof(suziSmooth), 2904, GL_TRIANGLES, "suziSmooth");
			suziSmoothModel->translate(spherePositions[i]);
			suziSmoothModel->scale(modelScale);
			lightScene->addObject(suziSmoothModel);
		}
		else if (i == 3)
		{
			Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES, "sphere");
			sphereModel->translate(spherePositions[i]);
			sphereModel->scale(modelScale);
			lightScene->addObject(sphereModel);
		}
	}

	// scene 2
	for (int i = 0; i < 55; i++) {
		Model* treeModel = new Model(shaderPhong, tree, sizeof(tree), 92814, GL_TRIANGLES, "tree");

		float randomX = (float)(rand() % 1000) / 100.0f - 5.0f;
		float groundY = 0.0f;
		float randomZ = (float)(rand() % 1000) / 100.0f - 5.0f;

		glm::vec3 treePosition = glm::vec3(randomX, groundY, randomZ);
		glm::vec3 treeScale = glm::vec3(0.03f + (float)(rand() % 10) / 100.0f);
		glm::vec3 treeRotate = glm::vec3(0.f, 0.8f, 0.f);
		float randomRotation = static_cast<float>(rand() % 360);

		treeModel->translate(treePosition);
		treeModel->scale(treeScale);
		treeModel->rotate(randomRotation, treeRotate);
		forestScene->addObject(treeModel);
	}

	for (int i = 0; i < 55; i++) {
		Model* bushModel = new Model(lambertShader, bushes, sizeof(bushes), 92814, GL_TRIANGLES, "bush");

		float randomX = (float)(rand() % 1000) / 100.0f - 5.0f;
		float groundY = 0.0f;
		float randomZ = (float)(rand() % 1000) / 100.0f - 5.0f;

		glm::vec3 bushPosition = glm::vec3(randomX, groundY, randomZ);
		glm::vec3 bushScale = glm::vec3(0.05f + (float)(rand() % 10) / 100.0f);
		glm::vec3 bushRotate = glm::vec3(0.f, 0.8f, 0.f);
		float randomRotation = static_cast<float>(rand() % 360);

		bushModel->translate(bushPosition);
		bushModel->scale(bushScale);
		bushModel->rotate(randomRotation, bushRotate);
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

	if (glfwGetKey(glfwWindow, GLFW_KEY_R) == GLFW_PRESS) {
		forestScene->rotateTrees();
		std::cout << "Rotate trees" << std::endl;
	}

	if (glfwGetKey(glfwWindow, GLFW_KEY_T) == GLFW_PRESS) {
		forestScene->translateBushes(5.0f);
		std::cout << "Translate bushes" << std::endl;
	}

	cameraController->processInput(glfwWindow, deltaTime);
}
