#include "Application.h"

float triangleVertices[] = {
    -0.3f,  0.8f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.3f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.4f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

     0.3f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.4f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
     0.1f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f
};

const float skycube[108] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};


Application::Application() : window(nullptr), currentScene(nullptr), primitiveScene(nullptr), forestScene(nullptr), nightForestScene(nullptr), sphereScene(nullptr), camera(nullptr), lightScene(nullptr), skyBoxScene(nullptr) {
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

    camera = new Camera(0.0f, 2.0f, 3.0f, 0.0f, 1.0f, 0.0f);
    cameraController = new CameraController(camera);

    primitiveScene = new Scene();
    forestScene = new Scene();
    nightForestScene = new Scene();
    sphereScene = new Scene();
    lightScene = new Scene();
    skyBoxScene = new Scene();

    Light* pointLight = new Light(0, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 1.0f, 0.09f, 0.0f);
    Light* directionalLight = new Light(1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f, 0.0f);
    Light* spotLight = new Light(2, camera->getPosition(), camera->getDirection(), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, glm::cos(glm::radians(12.5f)));

    std::vector<Light*> lights = { pointLight, directionalLight, spotLight };

    forestScene->setLight(pointLight);
    forestScene->setLight(directionalLight);
    forestScene->setLight(spotLight);

    Light* nightSpotLight = new Light(2, camera->getPosition(), camera->getDirection(), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.01f, glm::cos(glm::radians(12.5f)));

    std::vector<Light*> nightLights = { nightSpotLight };

    nightForestScene->setLight(spotLight);

    sphereScene->setLight(pointLight);
    lightScene->setLight(pointLight);

    // different shaders
    ShaderProgram* shaderPhong = new ShaderProgram(camera, lights);
    shaderPhong->create("./Shaders/phong_vertex_shader.glsl", "./Shaders/phong_fragment_shader.glsl");
    ShaderProgram* constantShader = new ShaderProgram(camera, lights);
    constantShader->create("./Shaders/constant_vertex_shader.glsl", "./Shaders/constant_fragment_shader.glsl");
    ShaderProgram* lambertShader = new ShaderProgram(camera, lights);
    lambertShader->create("./Shaders/lambert_vertex_shader.glsl", "./Shaders/lambert_fragment_shader.glsl");
    ShaderProgram* blinnShader = new ShaderProgram(camera, lights);
    blinnShader->create("./Shaders/blinn_vertex_shader.glsl", "./Shaders/blinn_fragment_shader.glsl");
    ShaderProgram* textureShader = new ShaderProgram(camera, lights);
    textureShader->create("./Shaders/vertex_shader.glsl", "./Shaders/fragment_shader.glsl");
    ShaderProgram* skyBoxShader = new ShaderProgram(camera, lights);
    skyBoxShader->create("./Shaders/skybox_vertex_shader.glsl", "./Shaders/skybox_fragment_shader.glsl");
    ShaderProgram* objectShader = new ShaderProgram(camera, lights);
    objectShader->create("./Shaders/object_vertex_shader.glsl", "./Shaders/object_fragment_shader.glsl");

    // materials
    Material* treeMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.3f, 0.3f, 0.3f));
    Material* bushMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.4f, 0.8f, 0.4f), glm::vec3(0.2f, 0.2f, 0.2f));
    Material* sphereMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* giftMaterial = new Material(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.8f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* suziFlatMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.4f, 0.8f, 0.4f), glm::vec3(0.4f, 0.4f, 0.4f));
    Material* suziSmoothMaterial = new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.4f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* triangleMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* plainMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));

    // textures
    Texture* triangleTexture = new Texture("./Textures/wooden_fence.png");
    Texture* plainTexture = new Texture("./Textures/grass.png");

    Model* triangleModel = new Model(textureShader, triangleVertices, sizeof(triangleVertices), 3, GL_TRIANGLES, "triangle", triangleMaterial, triangleTexture);
    Model* plainModelSkybox = new Model(textureShader, plain, sizeof(plain), 6, GL_TRIANGLES, "plain", plainMaterial, plainTexture);
    /*Model* plainModel = new Model(shaderPhong, plain, sizeof(plain), 6, GL_TRIANGLES, "plain", plainMaterial);*/

    glm::vec3 treePosition = glm::vec3(0.0f, 0.0f, -2.0f);
    glm::vec3 treeSize = glm::vec3(2.0f);

    glm::vec3 plainSize = glm::vec3(5.0f);

    glm::vec3 skyBoxSize = glm::vec3(5.0f);

    triangleModel->translate(treePosition);
    triangleModel->scale(treeSize);

    //plainModel->scale(plainSize);
    plainModelSkybox->scale(plainSize);

    primitiveScene->addObject(triangleModel);
    forestScene->addObject(plainModelSkybox);
    nightForestScene->addObject(plainModelSkybox);
    //forestScene->addObject(plainModel);
    //nightForestScene->addObject(plainModel);
    skyBoxScene->addObject(plainModelSkybox);

    
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
        Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES, "sphere", sphereMaterial);
        sphereModel->translate(spherePositions[i]);
        sphereModel->scale(modelScale);
        sphereScene->addObject(sphereModel);
    }

    // 4 scene
    for (int i = 0; i < 4; i++) {
        if (i == 0)
        {
            Model* giftModel = new Model(constantShader, gift, sizeof(gift), 66624, GL_TRIANGLES, "gift", giftMaterial);
            giftModel->translate(spherePositions[i]);
            giftModel->scale(giftScale);
            lightScene->addObject(giftModel);
        }
        else if (i == 1)
        {
            Model* suziFlatModel = new Model(lambertShader, suziFlat, sizeof(suziFlat), 2904, GL_TRIANGLES, "suziFlat", suziFlatMaterial);
            suziFlatModel->translate(spherePositions[i]);
            suziFlatModel->scale(modelScale);
            lightScene->addObject(suziFlatModel);
        }
        else if (i == 2)
        {
            Model* suziSmoothModel = new Model(blinnShader, suziSmooth, sizeof(suziSmooth), 2904, GL_TRIANGLES, "suziSmooth", suziSmoothMaterial);
            suziSmoothModel->translate(spherePositions[i]);
            suziSmoothModel->scale(modelScale);
            lightScene->addObject(suziSmoothModel);
        }
        else if (i == 3)
        {
            Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES, "sphere", sphereMaterial);
            sphereModel->translate(spherePositions[i]);
            sphereModel->scale(modelScale);
            lightScene->addObject(sphereModel);
        }
    }

    // scene 2 - forest scene with lights. 5 scene - night forest scene with spotlight and 6 scene - skybox
    for (int i = 0; i < 55; i++) {
        Model* treeModel = new Model(shaderPhong, tree, sizeof(tree), 92814, GL_TRIANGLES, "tree", treeMaterial);
        Model* treeModelSkyBox = new Model(objectShader, tree, sizeof(tree), 92814, GL_TRIANGLES, "tree", treeMaterial);

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

        treeModelSkyBox->translate(treePosition);
        treeModelSkyBox->scale(treeScale);
        treeModelSkyBox->rotate(randomRotation, treeRotate);

        forestScene->addObject(treeModel);
        nightForestScene->addObject(treeModel);
        skyBoxScene->addObject(treeModelSkyBox);
    }

    for (int i = 0; i < 55; i++) {
        Model* bushModel = new Model(lambertShader, bushes, sizeof(bushes), 92814, GL_TRIANGLES, "bush", bushMaterial);
        Model* bushModelSkyBox = new Model(objectShader, bushes, sizeof(bushes), 92814, GL_TRIANGLES, "bush", bushMaterial);

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

        bushModelSkyBox->translate(bushPosition);
        bushModelSkyBox->scale(bushScale);
        bushModelSkyBox->rotate(randomRotation, bushRotate);

        forestScene->addObject(bushModel);
        nightForestScene->addObject(bushModel);
        skyBoxScene->addObject(bushModelSkyBox);
    }

    currentScene = primitiveScene;
}

Application::~Application() {
    delete camera;
    delete cameraController;
    delete primitiveScene;
    delete forestScene;
    delete nightForestScene;
    delete sphereScene;
    delete lightScene;
	delete skyBoxScene;
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

		// Position and direction of the spotlight are updated together with the camera
        Light* spotLight = nightForestScene->getLights()[0];
        spotLight->setPosition(camera->getPosition());
        spotLight->setDirection(camera->getDirection());

        // Dynamic rotation
        forestScene->rotateTrees();

		//forestScene->translateBushes(5.0f);

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

    if (glfwGetKey(glfwWindow, GLFW_KEY_5) == GLFW_PRESS) {
        currentScene = nightForestScene;
        std::cout << "Scene 5" << std::endl;
    }

    if (glfwGetKey(glfwWindow, GLFW_KEY_6) == GLFW_PRESS) {
        currentScene = skyBoxScene;
        std::cout << "Scene 6" << std::endl;
    }

    /*if (glfwGetKey(glfwWindow, GLFW_KEY_R) == GLFW_PRESS) {
        forestScene->rotateTrees();
        std::cout << "Rotate trees" << std::endl;
    }*/

    if (glfwGetKey(glfwWindow, GLFW_KEY_T) == GLFW_PRESS) {
        forestScene->translateBushes(3.0f);
        std::cout << "Translate bushes" << std::endl;
    }

    cameraController->processInput(glfwWindow, deltaTime);
}