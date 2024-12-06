#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(Camera* camera, const std::vector<Light*> lights) : programID(0), camera(camera), lights(lights)
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
        if (camera) {
            setMat4("viewMatrix", camera->getViewMatrix());
            setMat4("projectionMatrix", camera->getProjectionMatrix(1.0f));
        }
    }

    if (message == "light")
    {
        if (light) {
            setVec3("lightPosition", light->getPosition());
            setVec3("lightColor", light->getColor());
            setFloat("lightIntensity", light->getIntensity());
            setFloat("lightAttenuation", light->getAttenuation());
        }
    }
   
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setLight(const std::string& name, const Light& light, int index) const {
	setInt(name + "[" + std::to_string(index) + "].type", light.getType());
	setVec4(name + "[" + std::to_string(index) + "].position", glm::vec4(light.getPosition(), 1.0f));
	setVec4(name + "[" + std::to_string(index) + "].direction", glm::vec4(light.getDirection(), 1.0f));
	setVec4(name + "[" + std::to_string(index) + "].diffuse", glm::vec4(light.getColor(), 1.0f));
	setFloat(name + "[" + std::to_string(index) + "].attenuation", light.getAttenuation());
	setFloat(name + "[" + std::to_string(index) + "].cutoff", light.getCutoff());
}