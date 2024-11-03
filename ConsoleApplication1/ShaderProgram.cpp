#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(Camera* camera, Light* light) : programID(0), camera(camera), light(light)
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

void ShaderProgram::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setMat3(const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::update(const char* message) {
	if (message == "camera") {
		setMat4("viewMatrix", camera->getViewMatrix());
		setMat4("projectionMatrix", camera->getProjectionMatrix(1.0f));
	}

	if (message == "light")
	{
		setVec3("lightPosition", light->getPosition());
		setVec3("lightColor", light->getColor());
		setFloat("lightIntensity", light->getIntensity());
	}
   
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
