#include "SurfaceImage.h"
#include "FileLoader.h"
SurfaceImage::SurfaceImage(const std::string& path)
    : textureID(0), FilePath(path), Buffer(nullptr), width(0), height(0), BitsPerPixel(0) {

    Buffer = FileLoader::LoadImage(path, width, height, BitsPerPixel);

    glGenTextures(1, &textureID); // Generate texture ID
    glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture ID

    // Set texture parameters (e.g., wrapping and filtering options)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image data into the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffer);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

SurfaceImage::~SurfaceImage()
{
	glDeleteTextures(1, &textureID);
}

void SurfaceImage::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void SurfaceImage::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
