#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <glm/fwd.hpp>

class Camera;

class ShaderProgram {
public:
    ShaderProgram(Camera* camera);
    ~ShaderProgram();

    void create(const char* vertexSource, const char* fragmentSource);
    void use();
	void setMat4(const std::string& name, const glm::mat4& mat) const;
    GLint getUniformLocation(const std::string& name);
    GLuint getProgramID() const;

private:
    GLuint programID;
    GLuint loadShader(const char* source, GLenum shaderType);
};

#endif // SHADERPROGRAM_H