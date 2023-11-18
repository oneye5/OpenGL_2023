#pragma once
class VertexArray
{
private:
public:
	VertexArray();
	~VertexArray();
		
	void addBuffer(const VertexBuffer& vertexBuffer, const vertexBufferLayout& layout);
};