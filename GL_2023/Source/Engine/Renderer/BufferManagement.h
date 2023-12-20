#include"GLM/glm-master/glm/glm.hpp"
#include <vector>
#include <GLM/glm-master/glm/gtx/transform.hpp>
#include <iostream>
using std::vector;
using glm::vec3;

static glm::mat4 MakeModelMatrixFromComponents(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale)
{
	// Create transformation matrices for translation, rotation, and scaling
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Pos);

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), Rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, Rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, Rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

	// Combine the transformation matrices to obtain the final transformation
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return transformationMatrix;
}



class BufferManagement
{
private:
	struct DynamicObject
	{
		unsigned int PositionInVertexBuffer;
		unsigned int SizeOnVertexBuffer;

		vector<unsigned int>* textureSlots;
		vector<vector<unsigned int>>* indicies;
		vec3* pos;
		vec3* rot;
		vec3* scale;

		DynamicObject(vector<vector<unsigned int>>* Indicies, vector<unsigned int>* TextureSlots,
			vec3* Pos, vec3* Rot, vec3* Scale, unsigned int positionInVertexBuffer,unsigned int floatSizeOnBuffer)
		{
			textureSlots = TextureSlots;
			indicies = Indicies;
			pos = Pos;
			rot = Rot;
			scale = Scale;

			positionInVertexBuffer = PositionInVertexBuffer;
			floatSizeOnBuffer = SizeOnVertexBuffer;
		}
	};	
	vector<vector<unsigned int>> StaticIndexBuffers;
public:
	const unsigned int floatsPerVertex = 8;

	struct IndexBufferGroup //used for defining what different objects are where on the index buffer, and what properties they have
	{
		unsigned int start;
		unsigned int size;
		unsigned int textureSlot;

		glm::mat4 ModelMatrix;
	};

	vector<IndexBufferGroup> IndexBufferGroups;
	vector<float> vertexBuffer;
	vector<unsigned int> indexBuffer;
	vector<DynamicObject> DynamicObjects;


	void PushToStaticBuffer(
		vector<float>* data, vector<vector<unsigned int>>* indicies, vector<unsigned int>* textureSlots,
		vec3* pos, vec3* rot, vec3* scale);

	void PushToDynamicBuffer
	(vector<float>* data, vector<vector<unsigned int>>* indicies,vector<unsigned int>* textureSlots,
		vec3* pos, vec3* rot, vec3* scale);
	

	void RefreshIndexBuffer()
	{
		indexBuffer.clear(); IndexBufferGroups.clear();
		//calculate the amount of items we need to reserve for the buffer to avoid re alocation of the memory on pushback
		unsigned int bufferSize = 0;
		unsigned int groupSize = 0;
		for (auto& obj : DynamicObjects)
		{
			groupSize += obj.indicies->size();
			for (int i = 0; i < obj.indicies->size(); i++)
			{
				bufferSize += obj.indicies->size();
			}
		}
		indexBuffer.reserve(bufferSize);


		//static stuff here



		//dynamic stuff here


		for (auto& obj : DynamicObjects)
		{
		
			auto modelMatrix = MakeModelMatrixFromComponents(*obj.pos,*obj.rot,*obj.scale);
			for (int i = 0; i < obj.indicies->size(); i++)
			{	
				IndexBufferGroup group;
				vector<unsigned int>& subBuffer = obj.indicies->at(i);
				unsigned int textureSlot = obj.textureSlots->at(i);

				group.ModelMatrix = modelMatrix;
				group.size = subBuffer.size();
				group.start = indexBuffer.size();
				group.textureSlot = textureSlot;

				for (auto& x : subBuffer)
					indexBuffer.push_back(x);

				IndexBufferGroups.push_back(group);
			}
		}


		std::cout << "done getting buffer";
	}
	
};
