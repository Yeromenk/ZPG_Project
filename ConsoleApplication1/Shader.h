#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader {
public:
    Shader();
    ~Shader();
    void createShaderPrograms(bool isQuad);
    void use();
    GLuint getProgramID();
private:
    GLuint shaderProgram;
    GLuint loadShader(const char* source, GLenum shaderType);
};

#endif