#include "Systems.h"
#include "Renderer.h"
#include "FileLoader.h"
#include "Mesh.h"

bool Mesh::PushToBuffer()
{
	if (data.size() == 0)
	{
		std::cout << "Mesh.cpp - Push to renderer - Error, no data to push";
		return false;
	}
	auto renderer = ENGINE_SYSTEMS::GET_RENDERER();
	
	if (Static)
	{
		renderer->BufferManager.PushToStaticBuffer(&data, &indicies,&TextureSlots,&assosiatedTransform->pos,&assosiatedTransform->rot,&assosiatedTransform->scale);
		return true;
	}
	//dynamic object
	renderer->BufferManager.PushToDynamicBuffer(&data, &indicies, &TextureSlots, &assosiatedTransform->pos, &assosiatedTransform->rot, &assosiatedTransform->scale);

	return true;
}
bool Mesh::LoadFile(std::string file)
{
	MeshLocation = FileLoader::GetWorkingDir() + "/Source/Client_Assets/GraphicsAssets/Meshes/" + file;
	bool successful = FileLoader::LoadMesh(MeshLocation,data,indicies);
	if (!successful)
		std::cout << "failed loading file at, '" + MeshLocation + "'";
	return successful;
}
