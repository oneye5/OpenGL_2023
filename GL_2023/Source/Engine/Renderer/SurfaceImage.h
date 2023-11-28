#pragma once
#include "Renderer.h"
class SurfaceImage
{
public:
	unsigned int RendererID;
	std::string FilePath;
	unsigned char* Buffer;
	int width, height, BitsPerPixel;

	SurfaceImage(const std::string& path);
	~SurfaceImage();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};
