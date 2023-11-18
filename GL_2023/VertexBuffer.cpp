#include "VertexBuffer.h"
#include "Renderer.h";
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //vertex buffer
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER,size, data, GL_STATIC_DRAW);//buffer size
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&rendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
