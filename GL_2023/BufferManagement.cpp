#include "BufferManagement.h"

void BufferManagement::PushToStaticBuffer(vector<float>* data, vector<vector<unsigned int>>* indicies, vector<unsigned int>* textureSlots, vec3* pos, vec3* rot, vec3* scale)
{
	//add model matrix here

	//THIS IS TERRIBLY BROKEN FIX THIS PLEASE

	unsigned int BufferPosition = vertexBuffer.size();
	for (int i = 0; i < data->size(); i++)
	{
		vertexBuffer.push_back(data->at(i));
	}



	for (int i = 0; i < indicies->size(); i++)
	{
		vector<unsigned int> buffer = indicies->at(i);
		for (int i = 0; i < buffer.size(); i++)
				buffer[i] += BufferPosition;
	}
	for (auto buffer : StaticIndexBuffers)
		StaticIndexBuffers.push_back(buffer);
	
	for(int i = 0; i < textureSlots->size(); i++) //add texture slots to the buffer, each index buffer has a texture slot 
		textureSlots->push_back(textureSlots->at(i));

}

void BufferManagement::PushToDynamicBuffer(vector<float>* data, vector<vector<unsigned int>>* indicies, vector<unsigned int>* textureSlots, vec3* pos, vec3* rot, vec3* scale)
{
	unsigned int BufferPos = vertexBuffer.size();
	unsigned int size = data->size();
	
	vertexBuffer.reserve(vertexBuffer.size() + data->size());
	for (unsigned int i = 0; i < data->size(); i++)
		vertexBuffer.push_back(data->at(i));
	
	DynamicObjects.push_back(DynamicObject(indicies, textureSlots, pos, rot, scale, BufferPos, size));
}
