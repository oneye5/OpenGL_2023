#include"GLM/glm-master/glm/glm.hpp"
#include <vector>

using std::vector;
using glm::vec3;
class BufferManagement
{
private:
	struct DynamicObject
	{
		vector<unsigned int>* textureSlots;
		vector<float>* data;
		vector<vector<unsigned int>>* indicies;
		vec3* pos;
		vec3* rot;
		vec3* scale;

		DynamicObject(vector<float>* Data, vector<vector<unsigned int>>* Indicies, vector<unsigned int>* TextureSlots,
			vec3* Pos, vec3* Rot, vec3* Scale)
		{
			textureSlots = TextureSlots;
			data = Data;
			indicies = Indicies;
			pos = Pos;
			rot = Rot;
			scale = Scale;
		}
	};
public:
	const unsigned int floatsPerVertex = 8;
	vector<float> vertexBuffer;
	vector<vector<unsigned int>> StaticIndexBuffers;
	vector<DynamicObject> DynamicObjects;
	void PushToStaticBuffer(
		vector<float>* data, vector<vector<unsigned int>>* indicies, vector<unsigned int>* textureSlots,
		vec3* pos, vec3* rot, vec3* scale);

	void PushToDynamicBuffer
	(vector<float>* data, vector<vector<unsigned int>>* indicies,vector<unsigned int>* textureSlots,
		vec3* pos, vec3* rot, vec3* scale);
	
};
