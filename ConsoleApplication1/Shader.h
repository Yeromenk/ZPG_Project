#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader {
public:
    Shader();
    ~Shader();

    void use();
    void use_quad();

    GLuint getProgramID();
    GLuint getProgramID_quad();
private:
    GLuint shaderProgram;
    GLuint shaderProgram_quad;
    GLuint loadShader(const char* source, GLenum shaderType);
};

#endif