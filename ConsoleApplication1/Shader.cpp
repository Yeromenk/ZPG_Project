#include "Shader.h"
#include <iostream>

// Constructor: Initializes shader program IDs to 0.
Shader::Shader(Camera* camera) : shaderProgram(0), shaderProgram_quad(0)
{
	this->camera = camera;
}

// Destructor: Deletes the shader programs.
Shader::~Shader() {
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram_quad);
}

// Activates the main shader program.
void Shader::use() {
    glUseProgram(shaderProgram);
}

// Activates the quad shader program.
void Shader::use_quad() {
    glUseProgram(shaderProgram_quad);
}

// Loads and compiles a shader from source code.
GLuint Shader::loadShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

// Returns the ID of the main shader program.
GLuint Shader::getProgramID() {
    return shaderProgram;
}

// Returns the ID of the quad shader program.
GLuint Shader::getProgramID_quad() {
    return shaderProgram_quad;
}