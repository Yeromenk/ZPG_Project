#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>


class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    void create(const char* vertexSource, const char* fragmentSource);
    void use();
    GLint getUniformLocation(const std::string& name);

private:
    GLuint programID;
    GLuint loadShader(const char* source, GLenum shaderType);
};

#endif // SHADERPROGRAM_H
