#include "Systems.h"
#include "Renderer.h"
#include "FileLoader.h"
#include "Mesh.h"

bool Mesh::PushToRenderer(bool keepCopyOnStack)
{
	if (data.size() == 0)
	{
		std::cout << "Mesh.cpp - Push to renderer - Error, no data to push";
		return false;
	}
	


	return true;
}
bool Mesh::LoadFile(std::string file)
{
	MeshLocation = file;
	bool successful = FileLoader::LoadMesh(FileLoader::GetWorkingDir() +"/" + file,data,indicies);
	
	return successful;
}
