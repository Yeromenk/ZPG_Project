#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <glm/fwd.hpp>

#include "Observer.h"
#include "Camera.h"
#include "ShaderLoader.h"

class Camera;

class ShaderProgram : public Observer {
public:
    ShaderProgram(Camera* camera);
    ~ShaderProgram();

    void create(const char* vertexFile, const char* fragmentFile);
    void use();
	void setMat4(const std::string& name, const glm::mat4& mat) const;
    void update(const char* message) override;

private:
	Camera* camera;
    GLuint programID;
	ShaderLoader shaderLoader;
};

#endif // SHADERPROGRAM_H