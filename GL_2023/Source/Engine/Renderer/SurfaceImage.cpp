#include "SurfaceImage.h"
#include "FileLoader.h"
SurfaceImage::SurfaceImage(const std::string& path)
{
	Buffer = FileLoader::LoadImage(path, width, height, BitsPerPixel);
	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_2D, RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffer);
	Unbind();
}

SurfaceImage::~SurfaceImage()
{

}

void SurfaceImage::Bind(unsigned int slot) const
{

}

void SurfaceImage::Unbind() const
{

}
