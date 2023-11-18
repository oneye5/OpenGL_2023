#pragma once
class IndexBuffer
{
private:
	unsigned int	rendererID;

	public:
	unsigned int count;
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	
	void Bind() const;
	void Unbind() const;

};