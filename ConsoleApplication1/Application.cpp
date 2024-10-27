#include "Application.h"

#include "Model.h"

// Define vertex arrays
float triangleVertices[] = {
    -0.3f,  0.8f, 0.0f,  0.3f,  0.5f, 0.0f,
    -0.4f, 0.5f, 0.0f,  0.3f, 0.5f, 0.0f,
    0.1f, 0.6f, 0.0f, 0.9f, 0.5f, 0.0f
};

float rectangleVertices[] = {
    -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f,
};

Application::Application() : window(nullptr), currentScene(nullptr), primitiveScene(nullptr), forestScene(nullptr), camera(nullptr) {
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

    camera = new Camera(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f);
    cameraController = new CameraController(camera);

    primitiveScene = new Scene();
    forestScene = new Scene();

    // Initialize primitive scene
    ShaderProgram* shader1 = new ShaderProgram(camera);
    shader1->create("./Shaders/vertex_shader.glsl", "./Shaders/fragment_shader.glsl");
    ShaderProgram* shader2 = new ShaderProgram(camera);
    shader2->create("./Shaders/vertex_shader.glsl", "./Shaders/fragment_shader.glsl");

	Model* triangleModel = new Model(shader1, triangleVertices, sizeof(triangleVertices), 3, GL_TRIANGLES);
	Model* rectangleModel = new Model(shader2, rectangleVertices, sizeof(rectangleVertices), 6, GL_TRIANGLES);

    primitiveScene->addObject(triangleModel);
	primitiveScene->addObject(rectangleModel);

	Model* plainModel = new Model(shader1, plain, sizeof(plain), 6, GL_TRIANGLES);
	forestScene->addObject(plainModel);

    for (int i = 0; i < 5; i++) {
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

    for (int i = 0; i < 3; i++) {
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

    cameraController->processInput(glfwWindow, deltaTime);

}