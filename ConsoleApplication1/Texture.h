#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <vector>

class Texture {
public:
    Texture();
    ~Texture();

    void bind(GLuint textureUnit) const;
    void unbind() const;

	void loadTexture(const char* filePath, int unit_id);
	void loadCubeMap(const char* xpos, const char* xneg, const char* ypos, const char* yneg, const char* zpos, const char* zneg, int unitId);

private:
    GLuint textureID;
	int unitId;
};

#endif // TEXTURE_H