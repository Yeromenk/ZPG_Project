#include "ShaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(Camera* camera) : programID(0)
{
	
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::create(const char* vertexFile, const char* fragmentFile) {
    programID = shaderLoader.loadShader(vertexFile, fragmentFile);

}

void ShaderProgram::use() {
    glUseProgram(programID);
}

//GLint ShaderProgram::getUniformLocation(const std::string& name) {
//    return glGetUniformLocation(programID, name.c_str());
//}

//GLuint ShaderProgram::loadShader(const char* source, GLenum shaderType) {
//    GLuint shader = glCreateShader(shaderType);
//    glShaderSource(shader, 1, &source, nullptr);
//    glCompileShader(shader);
//
//    GLint success;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        char infoLog[512];
//        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
//        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    return shader;
//}

//GLuint ShaderProgram::getProgramID() const {
//	return programID;
//}

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::update(const char* message) {
	if (message == "camera") {
		setMat4("view", camera->getViewMatrix());
		setMat4("projection", camera->getProjectionMatrix(1.0f));
	}
}