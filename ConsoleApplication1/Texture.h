#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>
#include <string>

class Texture {
public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind(GLuint textureUnit) const;
    void unbind() const;

private:
    GLuint textureID;
};

#endif // TEXTURE_H