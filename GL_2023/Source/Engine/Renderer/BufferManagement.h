#include <vector>
#include"GLM/glm-master/glm/glm.hpp"
#include "Transform.h"
#include "Mesh.h"

using std::vector;
using glm::vec3;



class DynamicObject
{
public:
	Mesh* mesh = nullptr;
	Transform* transform = nullptr;
	DynamicObject(Mesh* m, Transform* t)
	{
		mesh = m; transform = t;
	}
};
class BufferManagement
{
public:
	const unsigned int floatsPerVertex = 8;
	vector<float> vertexBuffer;
	vector<vector<unsigned int>> StaticIndexBuffers; //last int represents the texture slot
	vector<DynamicObject> DynamicObjects;
	void PushToStaticBuffer(vector<float>& data, vector<vector<unsigned int>>& indicies)
	{

	}
};
