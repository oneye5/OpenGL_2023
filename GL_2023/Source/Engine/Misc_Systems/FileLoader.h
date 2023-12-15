#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <direct.h>
#include <stb_image.h>

using std::string;
using std::vector;
static class FileLoader
{
public:
	/// <summary>
	/// Loads a specified .obj file using a full path and reformats and indexes the data for use by OpenGL. use GetWorkingDir() to make it relative to the project.
	/// </summary>
	/// <param name="data">Used as an output. Adds data for the verticies, including positon, normal and uv data.</param>
	/// <param name="indicies">Used as an output. Each index refers to a set of vertex data.</param>
	/// <returns>Returns false if the method fails.</returns>
	static bool LoadMesh(std::string path,std::vector<float>& dataOut, vector<vector<unsigned int>>& indiciesOut)
	{
		dataOut.clear(); indiciesOut.clear();

		std::vector<glm::vec3> verticies, normals; std::vector<glm::vec2> uv; std::vector<std::vector<unsigned int>> faceIndiciesGroups;
	

			std::ifstream fileStream(path);
			if (!fileStream.is_open()) {
				std::cout << "failed to open file in loadmesh";
				return false;
			}

			std::string line;std::vector<unsigned int> faceIndicies;
			while (std::getline(fileStream, line))
			{
				
				std::istringstream lineStream(line);
				std::string prefix;
				lineStream >> prefix;

				if (prefix == "v") //vertex
				{
					glm::vec3 vertex;
					lineStream >> vertex.x >> vertex.y >> vertex.z;
					verticies.push_back(vertex);
				}
				else if (prefix == "vn") //norm
				{
					glm::vec3 norm;
					lineStream >> norm.x >> norm.y >> norm.z;
					normals.push_back(norm);
				}
				else if (prefix == "vt") //uv's
				{
					glm::vec2 texCoord;
					lineStream >> texCoord.x >> texCoord.y;
					uv.push_back(texCoord);
				}
				else if (prefix == "f") //indicies
				{
					std::string s1, s2, s3;
					lineStream >> s1 >> s2 >> s3;
					std::vector<std::string> args;
					std::string arg;
					for (auto x : s1)
					{
						if (x == '/')
						{
							args.push_back(arg);
							arg = "";
							continue;
						}
						arg += x;
					}
					args.push_back(arg);
					arg = "";
					for (auto x : s2)
					{
						if (x == '/')
						{
							args.push_back(arg);
							arg = "";
							continue;
						}
						arg += x;
					}
					args.push_back(arg);
					arg = "";
					for (auto x : s3)
					{
						if (x == '/')
						{
							args.push_back(arg);
							arg = "";
							continue;
						}
						arg += x;
					}
					args.push_back(arg);
					arg = "";




					//cast to unsigned int
					for (auto x : args)
					{
						faceIndicies.push_back(std::stoi(x));
					}
				}
				else if (prefix == "usemtl")
				{
					if (faceIndicies.size() != 0)
					{
						faceIndiciesGroups.push_back(faceIndicies);
						faceIndicies.clear();
					}
				}
			}
			faceIndiciesGroups.push_back(faceIndicies);
	



		//file is now done loading, put it into a format that opengl can use
		
		vector<vector<vector<float>>> objectDataGroups; //contains sets of data for every object
		for (auto faceIndicies2 : faceIndiciesGroups)
		{
			vector<vector<float>> dataGroup;
			for (int i = 0; i < faceIndicies2.size(); i += 3)//+=3 because indicies are grouped in lots of 3
			{
				vector<float> floats;
				floats.push_back(verticies[faceIndicies2[i] - 1].x);
				floats.push_back(verticies[faceIndicies2[i] - 1].y);
				floats.push_back(verticies[faceIndicies2[i] - 1].z);

				floats.push_back(normals[faceIndicies2[i + 2] - 1].x);
				floats.push_back(normals[faceIndicies2[i + 2] - 1].y);
				floats.push_back(normals[faceIndicies2[i + 2] - 1].z);

				floats.push_back(uv[faceIndicies2[i + 1] - 1].x);
				floats.push_back(uv[faceIndicies2[i + 1] - 1].y);

				dataGroup.push_back(floats);
			}
			objectDataGroups.push_back(dataGroup);
		}


		vector<vector<float>> allDifferentDataGroups; //contains every different set of 8 floats, no duplicates, used for indexing
		for (auto group : objectDataGroups)
		{
			vector<unsigned int> newIndexGroup;
			for (auto vertexData : group)
			{
				auto iterator = std::find(allDifferentDataGroups.begin(), allDifferentDataGroups.end(), vertexData);
				if (iterator != allDifferentDataGroups.end())//found
				{
					unsigned int index = std::distance(allDifferentDataGroups.begin(), iterator);
					newIndexGroup.push_back(index);
				}
				else
				{
					allDifferentDataGroups.push_back(vertexData);
					newIndexGroup.push_back(vertexData.size() - 1);
				}
			}
			indiciesOut.push_back(newIndexGroup);
		}
	
		//now put the groups of 8 floats into a single string of floats
		for (auto group : allDifferentDataGroups)
			for (auto vertexFloat : group)
				dataOut.push_back(vertexFloat);
		
		return true;
	}

	static void IndexRawMeshData(const std::vector<float>& inData, std::vector<float>& vertexBufferData, std::vector<unsigned int>& indexBufferData) //UNSUSED CURRENTLY
	{
		// Assuming each vertex has 8 floats: position (x, y, z), normal (nx, ny, nz), UV (u, v)
		const int floatsPerVertex = 8;

		// Assuming three indices per triangle (since typical OBJ data uses triangles)
		const int indicesPerTriangle = 3;

		// Assuming the indices are in sequential order in the faceIndices vector
		for (unsigned int i = 0; i < inData.size() / floatsPerVertex; i++) {
			// Extract each vertex's data from the outData vector
			for (int j = 0; j < floatsPerVertex; j++) {
				vertexBufferData.push_back(inData[i * floatsPerVertex + j]);
			}
		}

		// Generating indices based on the number of vertices
		for (unsigned int i = 0; i < vertexBufferData.size() / floatsPerVertex; i += indicesPerTriangle) {
			indexBufferData.push_back(i);
			indexBufferData.push_back(i + 1);
			indexBufferData.push_back(i + 2);
		}
	}

	static unsigned char* LoadImage(std::string path,int& w,int& h,int& bitsPerPixel)
	{
		stbi_set_flip_vertically_on_load(1);
		return stbi_load(path.c_str(), &w, &h, &bitsPerPixel, 4);
	}

	static string GetFileContents(const string& location)
	{
		std::cout << "loading file " << location << "\n";

		std::ifstream file(location);

		if (!file.is_open())
		{
			std::cout << "failed loading " << location << "\n";
			return "";
		}

		std::stringstream vertexBuffer;
		vertexBuffer << file.rdbuf();
		file.close();
		return vertexBuffer.str();
	}
	static string GetWorkingDir()
	{
		char cwd[256];
		_getcwd(cwd, 256);
		std::string cwd_str = std::string(cwd);
		return cwd_str;
	}
};