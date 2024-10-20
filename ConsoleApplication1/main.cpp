
/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Yeromenko Maksym
  **/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"

int main(void) {
    Application* app = new Application();
    app->run();  

    delete app;  
    return 0;
}
