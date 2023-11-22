#pragma once
#include "Renderer.h"
class IndexBuffer
{
	unsigned int ID;
	void Init(std::vector<unsigned int> indicies)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indicies, GL_STATIC_DRAW);//buffer size
	}
};