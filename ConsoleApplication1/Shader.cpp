#include "Shader.h"
#include <iostream>

Shader::Shader() {}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::createShaderPrograms(bool isQuad) {
    const char* vertex_shader =
        "#version 330\n"
        "layout(location = 0) in vec3 vp;\n"
        "layout(location = 1) in vec3 normal;\n"
        "uniform mat4 modelMatrix;\n"
        "void main() {\n"
        "    gl_Position = modelMatrix * vec4(vp, 1.0);\n"
        "}";

    const char* fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
        "}";

	const char* fragment_shader_quad =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4(1.0, 1.0, 0.0, 1.0);"
		"}";

    GLuint vertexShader = loadShader(vertex_shader, GL_VERTEX_SHADER);
	GLuint fragmentShader = isQuad ? loadShader(fragment_shader_quad, GL_FRAGMENT_SHADER) : loadShader(fragment_shader, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::cerr << "Failed to link shader program\n";
    }
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

GLuint Shader::loadShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return shader;
}

GLuint Shader::getProgramID() {
    return shaderProgram;  
}

