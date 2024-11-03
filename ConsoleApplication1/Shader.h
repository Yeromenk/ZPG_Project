#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Camera; 

class Shader {
public:
    Shader(Camera* camera);
    ~Shader();

    void use();
    
    GLuint getProgramID();

private:
    GLuint shaderProgram;
    GLuint shaderProgram_quad;
    Camera* camera;

    GLuint loadShader(const char* source, GLenum shaderType);
};

#endif 