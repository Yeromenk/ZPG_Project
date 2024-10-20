#include "Application.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Tree.h"
#include "Bush.h"

const char* vertexShaderSource1 =
"#version 330\n"
"layout(location=0) in vec3 vp;\n"
"layout(location=1) in vec3 normal;\n"
"out vec3 fragNormal;\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectionMatrix;\n"
"void main () {\n"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);\n"
"     fragNormal = normal;\n"
"}";

const char* fragmentShaderSource1 =
"#version 330\n"
"in vec3 fragNormal;\n"
"out vec4 frag_colour;\n"
"void main () {\n"
"     vec3 color = fragNormal * 0.5 + 0.5;\n"
"     frag_colour = vec4(color, 1.0);\n"
"}";

const char* vertexShaderSource2 = vertexShaderSource1;
const char* fragmentShaderSource2 = fragmentShaderSource1;

const char* vertexShaderSource = vertexShaderSource1;
const char* fragmentShaderSource = fragmentShaderSource1;

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

    primitiveScene = new Scene();
    forestScene = new Scene();

    // Initialize primitive scene
    ShaderProgram* shader1 = new ShaderProgram(camera);
    shader1->create(vertexShaderSource1, fragmentShaderSource1);
    ShaderProgram* shader2 = new ShaderProgram(camera);
    shader2->create(vertexShaderSource2, fragmentShaderSource2);

    Triangle* triangle = new Triangle(shader1, triangleVertices, sizeof(triangleVertices));
    Rectangle* rectangle = new Rectangle(shader2, rectangleVertices, sizeof(rectangleVertices));

    primitiveScene->addObject(triangle);
    primitiveScene->addObject(rectangle);

    ShaderProgram* treeShader = new ShaderProgram(camera);
    treeShader->create(vertexShaderSource, fragmentShaderSource);
    ShaderProgram* bushShader = new ShaderProgram(camera);
    bushShader->create(vertexShaderSource, fragmentShaderSource);

    for (int i = 0; i < 5; i++) {
        Tree* tree = new Tree(treeShader);
        glm::vec3 treePosition = glm::vec3((float)(rand() % 200) / 100.0f - 1.0f, (float)(rand() % 200) / 100.0f - 1.0f, 0.0f);
        glm::vec3 treeScale = glm::vec3(0.03f + (float)(rand() % 10) / 100.0f);
        glm::vec3 treeRotate = glm::vec3(0.f, 0.8f, 0.f);
        float randomRotation = static_cast<float>(rand() % 360);

        tree->translate(treePosition);
        tree->scale(treeScale);
        tree->rotate(randomRotation, treeRotate);

        forestScene->addObject(tree);
    }

    for (int i = 0; i < 3; i++) {
        Bush* bush = new Bush(bushShader);
        glm::vec3 bushPosition = glm::vec3((float)(rand() % 200) / 100.0f - 1.0f, (float)(rand() % 200) / 100.0f - 1.0f, 0.0f);
        glm::vec3 bushScale = glm::vec3(0.3f + (float)(rand() % 100) / 100.0f);
        glm::vec3 bushRotate = glm::vec3(0.f, 0.8f, 0.f);
        float randomRotation = static_cast<float>(rand() % 360);

        bush->translate(bushPosition);
        bush->scale(bushScale);
        bush->rotate(randomRotation, bushRotate);
        forestScene->addObject(bush);
    }


    currentScene = primitiveScene;
}

Application::~Application() {
    delete camera;
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

        camera->processMouseMovement(xoffset, yoffset);

        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 projectionMatrix = camera->getProjectionMatrix(800.0f / 600.0f);

        currentScene->draw(viewMatrix, projectionMatrix);

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

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS) {
        camera->move_forward(deltaTime);
    }
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS) {
        camera->move_backward(deltaTime);
    }
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS) {
        camera->move_left(deltaTime);
    }
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS) {
        camera->move_right(deltaTime);
    }
}
