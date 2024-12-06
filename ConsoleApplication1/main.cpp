
/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Yeromenko Maksym | YER0013
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
