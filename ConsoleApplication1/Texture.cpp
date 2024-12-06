#include "Texture.h"


Texture::Texture() {
	this->textureID = -1;
    this->unitId = -1;
}

void Texture::loadTexture(const char* filePath, int unitId)
{
    this->unitId = unitId;
    glActiveTexture(GL_TEXTURE0 + unitId);
    this->textureID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (this->textureID == 0) {
        std::cerr << "2D texture failed to load." << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, this->unitId);
}

void Texture::loadCubeMap(const char* xpos, const char* xneg, const char* ypos, const char* yneg, const char* zpos, const char* zneg, int unitId)
{
    this->unitId = unitId;
    glActiveTexture(GL_TEXTURE0 + unitId);
    this->textureID = SOIL_load_OGL_cubemap(xpos, xneg, ypos, yneg, zpos, zneg, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	printf("Texture ID: %d\n", this->textureID); ///

    if (this->textureID == 0) {
        std::cerr << "Cubemap texture failed to load." << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::bind(GLuint textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
