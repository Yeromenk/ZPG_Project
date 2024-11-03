#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <glm/fwd.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Observer.h"
#include "Camera.h"
#include "Light.h"
#include "ShaderLoader.h"

class Camera;

class ShaderProgram : public Observer {
public:
    ShaderProgram(Camera* camera, Light* light);
    ~ShaderProgram();

    void create(const char* vertexFile, const char* fragmentFile);
    void use();
	void setMat4(const std::string& name, const glm::mat4& mat) const;
    void update(const char* message) override;
	void setVec3(const std::string& name, const glm::vec3& vec) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setFloat(const std::string& name, float value) const;

private:
	Camera* camera;
	Light* light;
    GLuint programID;
	ShaderLoader shaderLoader;
};

#endif 