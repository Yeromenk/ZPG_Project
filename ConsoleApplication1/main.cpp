
/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Yeromenko Maksym
  **/

#include "Application.h"

int main(void) {
    Application* app = new Application();
    app->initialization();  // initialization OpenGL

	// Loading shaders and models
    app->createShaders();
    app->createModels();
	app->run();  // Launch application

    delete app;  // Release of resources
    return 0;
}
