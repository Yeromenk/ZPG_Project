#include "Shader.h"
#include <iostream>

Shader::Shader(Camera* camera) : shaderProgram(0), shaderProgram_quad(0)
{
	this->camera = camera;
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram_quad);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

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

GLuint Shader::getProgramID() {
    return shaderProgram;
}
