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
	MeshLocation = file;
	bool successful = FileLoader::LoadMesh(FileLoader::GetWorkingDir() +"/" + file,data,indicies);
	
	return successful;
}
