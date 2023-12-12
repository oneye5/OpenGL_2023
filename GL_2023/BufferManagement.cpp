#include "BufferManagement.h"

void BufferManagement::PushToStaticBuffer(vector<float>* data, vector<vector<unsigned int>>* indicies, vector<unsigned int>* textureSlots, vec3* pos, vec3* rot, vec3* scale)
{
	//add model matrix here



	unsigned int BufferPosition = vertexBuffer.size();
	for (int i = 0; i < data->size(); i++)
	{
		vertexBuffer.push_back(data->at(i));
	}



	for (int i = 0; i < indicies->size(); i++)
	{
		vector<unsigned int> buffer = indicies->at(i);
		for (int i = 0; i < buffer.size(); i++)
			if (i < buffer.size() - 1) //ignores last item
				buffer[i] += BufferPosition;
	}
	for (auto buffer : StaticIndexBuffers)
		StaticIndexBuffers.push_back(buffer);

}

void BufferManagement::PushToDynamicBuffer(vector<float>* data, vector<vector<unsigned int>>* indicies, vector<unsigned int>* textureSlots, vec3* pos, vec3* rot, vec3* scale)
{
	DynamicObjects.push_back(DynamicObject(data, indicies, textureSlots, pos, rot, scale));
}
