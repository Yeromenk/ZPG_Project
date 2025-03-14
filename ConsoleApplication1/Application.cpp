#include "Application.h"

float triangleVertices[] = {
    -0.3f,  0.8f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.3f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.4f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

     0.3f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    -0.4f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
     0.1f,  0.6f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f
};


Application::Application() : window(nullptr), currentScene(nullptr), primitiveScene(nullptr), forestScene(nullptr), nightForestScene(nullptr), sphereScene(nullptr), camera(nullptr), lightScene(nullptr) {
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetWindowUserPointer(window, this);

    // scenes
    primitiveScene = new Scene();
    forestScene = new Scene();
    nightForestScene = new Scene();
    sphereScene = new Scene();
    lightScene = new Scene();

    // lights
	Spotlight* spotLight = new Spotlight(camera, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.02f, glm::cos(glm::radians(15.0f)));
	PointLight* pointLight = new PointLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f);
	DirectionalLight* directionalLight = new DirectionalLight(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f), 1.0f);

    std::vector<Light*> lights = { pointLight, directionalLight, spotLight };

    forestScene->setLight(pointLight);
    forestScene->setLight(directionalLight);
    forestScene->setLight(spotLight);

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
	ShaderProgram* blinnTextureShader = new ShaderProgram(camera, lights);
	blinnTextureShader->create("./Shaders/BlinnVertexShaderTexture.glsl", "./Shaders/BlinnFragmentShaderTexture.glsl");
	ShaderProgram* constantTextureShader = new ShaderProgram(camera, lights);
	constantTextureShader->create("./Shaders/ConstantVertexShaderTexture.glsl", "./Shaders/ConstantFragmentShaderTexture.glsl");
	ShaderProgram* lambertTextureShader = new ShaderProgram(camera, lights);
	lambertTextureShader->create("./Shaders/LambertVertexShaderTexture.glsl", "./Shaders/LambertFragmentShaderTexture.glsl");
	phongTextureShader = new ShaderProgram(camera, lights);
	phongTextureShader->create("./Shaders/PhongVertexShaderTexture.glsl", "./Shaders/PhongFragmentShaderTexture.glsl");
	

    // materials
    treeMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.3f, 0.3f, 0.3f));
    Material* bushMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.4f, 0.8f, 0.4f), glm::vec3(0.2f, 0.2f, 0.2f));
    Material* sphereMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* giftMaterial = new Material(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.8f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* suziFlatMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.4f, 0.8f, 0.4f), glm::vec3(0.4f, 0.4f, 0.4f));
    Material* suziSmoothMaterial = new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.4f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* triangleMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
    Material* plainMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f));
	Material* houseMaterial = new Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.7f, 0.7f, 0.7f));
	Material* loginMaterial = new Material(glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.7f, 0.7f, 0.7f));

    // textures
	Texture* triangleTexture = new Texture();
	triangleTexture->loadTexture("./Textures/wooden_fence.png", 0);
	Texture* plainTexture = new Texture();
	plainTexture->loadTexture("./Textures/grass.png", 0);
	Texture* houseTexture = new Texture();
	houseTexture->loadTexture("./Models/House/model.png", 0);
    Texture* skyBoxTexture = new Texture();
    skyBoxTexture->loadCubeMap("./Textures/posx.jpg","./Textures/negx.jpg" ,"./Textures/posy.jpg", "./Textures/negy.jpg", "./Textures/posz.jpg", "./Textures/negz.jpg", 1);
	treeTexture = new Texture();
	treeTexture->loadTexture("./Models/Tree/tree.png", 0);

	// models
    Model* triangleModel = new Model(textureShader, triangleVertices, sizeof(triangleVertices), 3, GL_TRIANGLES, "triangle", triangleMaterial,  generateUniqueID(), triangleTexture);
    Model* plainModel = new Model(lambertTextureShader, plain, sizeof(plain), 6, GL_TRIANGLES, "plain", plainMaterial, generateUniqueID(), plainTexture);
	Model* houseModel = new Model("./Models/House/model.obj", phongTextureShader, houseMaterial, houseTexture, "house", generateUniqueID());
	Model* loginModel = new Model("./Models/Login/login.obj", blinnTextureShader , loginMaterial, triangleTexture, "login", generateUniqueID());
    Model* skyBoxModel = new Model(skyBoxShader, skycube, sizeof(skycube), 36, GL_TRIANGLES, "skybox", nullptr, generateUniqueID(), skyBoxTexture);

	allObjects.push_back(triangleModel);
	allObjects.push_back(plainModel);
	allObjects.push_back(houseModel);
	allObjects.push_back(loginModel);
	allObjects.push_back(skyBoxModel);
	

    glm::vec3 treePosition = glm::vec3(0.0f, 0.0f, -2.0f);
    glm::vec3 treeSize = glm::vec3(2.0f);

	glm::vec3 housePosition = glm::vec3(6.5f, 0.0f, 0.0f);
	glm::vec3 houseSize = glm::vec3(0.1f);

	glm::vec3 loginPosition = glm::vec3(5.0f, 0.0f, 3.0f);

    glm::vec3 plainSize = glm::vec3(7.0f);


    triangleModel->translate(treePosition);
    triangleModel->scale(treeSize);

	houseModel->translate(housePosition);
	houseModel->scale(houseSize);

	loginModel->translate(loginPosition);

    plainModel->scale(plainSize);

    primitiveScene->addObject(triangleModel);

    forestScene->addObject(plainModel);
	forestScene->addObject(houseModel);
	forestScene->addObject(loginModel);
    forestScene->addObject(skyBoxModel);

    nightForestScene->addObject(plainModel);
	nightForestScene->addObject(houseModel);
	nightForestScene->addObject(loginModel);

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
        Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES, "sphere", sphereMaterial, generateUniqueID(), nullptr);
        sphereModel->translate(spherePositions[i]);
        sphereModel->scale(modelScale);
        sphereScene->addObject(sphereModel);
    }

    // 4 scene
    for (int i = 0; i < 4; i++) {
        if (i == 0)
        {
            Model* giftModel = new Model(constantShader, gift, sizeof(gift), 66624, GL_TRIANGLES, "gift", giftMaterial, generateUniqueID(), nullptr);
            giftModel->translate(spherePositions[i]);
            giftModel->scale(giftScale);
            lightScene->addObject(giftModel);
        }
        else if (i == 1)
        {
            Model* suziFlatModel = new Model(lambertShader, suziFlat, sizeof(suziFlat), 2904, GL_TRIANGLES, "suziFlat", suziFlatMaterial ,generateUniqueID(), nullptr);
            suziFlatModel->translate(spherePositions[i]);
            suziFlatModel->scale(modelScale);
            lightScene->addObject(suziFlatModel);
        }
        else if (i == 2)
        {
            Model* suziSmoothModel = new Model(blinnShader, suziSmooth, sizeof(suziSmooth), 2904, GL_TRIANGLES, "suziSmooth", suziSmoothMaterial, generateUniqueID(), nullptr);
            suziSmoothModel->translate(spherePositions[i]);
            suziSmoothModel->scale(modelScale);
            lightScene->addObject(suziSmoothModel);
        }
        else if (i == 3)
        {
            Model* sphereModel = new Model(shaderPhong, sphere, sizeof(sphere), 2880, GL_TRIANGLES, "sphere", sphereMaterial, generateUniqueID(), nullptr);
            sphereModel->translate(spherePositions[i]);
            sphereModel->scale(modelScale);
            lightScene->addObject(sphereModel);
        }
    }

    // scene 2 - forest scene with lights. 5 scene - night forest scene with spotlight
    for (int i = 0; i < 55; i++) {
        Model* treeModel = new Model("./Models/Tree/tree.obj", phongTextureShader, treeMaterial, treeTexture, "tree", generateUniqueID());

        float randomX = (float)(rand() % 1000) / 100.0f - 5.0f;
        float groundY = 0.0f;
        float randomZ = (float)(rand() % 1000) / 100.0f - 5.0f;

        glm::vec3 treePosition = glm::vec3(randomX, groundY, randomZ);
        glm::vec3 treeScale = glm::vec3(0.015f + (float)(rand() % 5) / 100.0f);
        glm::vec3 treeRotate = glm::vec3(0.f, 0.8f, 0.f);
        float randomRotation = static_cast<float>(rand() % 360);

        treeModel->translate(treePosition);
        treeModel->scale(treeScale);
        treeModel->rotate(randomRotation, treeRotate);

        forestScene->addObject(treeModel);
        nightForestScene->addObject(treeModel);
    }

    for (int i = 0; i < 55; i++) {
        Model* bushModel = new Model(shaderPhong, bushes, sizeof(bushes), 92814, GL_TRIANGLES, "bush", bushMaterial, generateUniqueID(), nullptr);

        float randomX = (float)(rand() % 1000) / 100.0f - 5.0f;
        float groundY = 0.0f;
        float randomZ = (float)(rand() % 1000) / 100.0f - 5.0f;

        glm::vec3 bushPosition = glm::vec3(randomX, groundY, randomZ);
        glm::vec3 bushScale = glm::vec3(0.3f + (float)(rand() % 10) / 100.0f);
        glm::vec3 bushRotate = glm::vec3(0.f, 0.8f, 0.f);
        float randomRotation = static_cast<float>(rand() % 360);

        bushModel->translate(bushPosition);
        bushModel->scale(bushScale);
        bushModel->rotate(randomRotation, bushRotate);

        forestScene->addObject(bushModel);
        nightForestScene->addObject(bushModel);
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

	delete treeMaterial;

	delete treeTexture;
	delete phongTextureShader;

	for (auto object : allObjects) {
		delete object;
	}


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

        glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

        for (auto& object :  allObjects)
        {
            if (object->getType() != "skybox") {
                glStencilFunc(GL_ALWAYS, object->getID(), 0xFF);
                object->draw(camera->getViewMatrix(), camera->getProjectionMatrix(800.0f / 600.0f));
            }
        }

		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);

        glDisable(GL_STENCIL_TEST);

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
        Spotlight* spotLight = dynamic_cast<Spotlight*>(nightForestScene->getLights()[0]);
        if (spotLight) {
            spotLight->update();
        }

        // Dynamic rotation
        forestScene->rotateTrees();
		//forestScene->translateBushes(5.0f);

		currentScene->drawSkybox(camera);
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

void Application::updateProjectionMatrix(int width, int height) {
	glViewport(0, 0, width, height);
	camera->setProjectionMatrix(camera->getProjectionMatrix((float)width / (float)height));
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (app) 
    {
        app->updateProjectionMatrix(width, height);
    }
}

void Application::handleMouseClick()
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	GLuint x = static_cast<GLuint>(xpos);
	GLuint y = static_cast<GLuint>(ypos);
    int windowHeight;
	glfwGetWindowSize(window, nullptr, &windowHeight);
	int newY = windowHeight - y;

    GLuint index;
    glReadPixels(x, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d with stencil index %d\n", x, y, index);

    if(index == 0)
    {
        return;
    }

    // Read depth value
    GLfloat depth;
    glReadPixels(x, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    // Calculate world coordinates
    glm::vec3 screenPos = glm::vec3(x, newY, depth);
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix(static_cast<float>(800) / 600); // Assuming window size 800x600
    glm::vec4 viewport = glm::vec4(0, 0, 800, 600);

    glm::vec3 worldPos = glm::unProject(screenPos, view, projection, viewport);
    printf("World Position: [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);

    // Identify the clicked object using the stencil index
    DrawableObject* clickedObject = getObjectByID(index);
    if (clickedObject) {
        printf("Clicked Object Type: %s\n", clickedObject->getType().c_str());
    }

    // Instantiate a new tree at the clicked position
    addTreeAtPosition(worldPos);
}

void Application::addTreeAtPosition(glm::vec3& position)
{
    // Assume you have a method to generate unique IDs
    int newID = generateUniqueID();

    // Create a new tree model
    Model* newTree = new Model("./Models/Tree/tree.obj", phongTextureShader, treeMaterial, treeTexture, "tree", newID);


    glm::vec3 treeScale = glm::vec3(0.03f);

    // Set transformations
    newTree->translate(position);
    newTree->scale(treeScale); // Adjust scale as needed

    // Add to allObjects and currentScene
    allObjects.push_back(newTree);
    forestScene->addObject(newTree);
    nightForestScene->addObject(newTree);
}

int Application::generateUniqueID()
{
	static int currentId = 1;
	return currentId++;
}


void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) {
            app->handleMouseClick();
        }
    }
}

DrawableObject* Application::getObjectByID(int id)
{
	for (auto& object : allObjects)
	{
		if (object->getID() == id)
		{
			return object;
		}
	}
	return nullptr;
}