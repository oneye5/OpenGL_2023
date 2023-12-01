#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <direct.h>
#include <stb_image.h>

using std::string;
static class FileLoader
{
public:
	static bool LoadMesh(std::string path,std::vector<float>& data, std::vector<unsigned int>& indicies)
	{
		std::vector<glm::vec3> verticies, normals; std::vector<glm::vec2> uv; std::vector<unsigned int> faceIndicies;


		std::ifstream fileStream(path);
		if (!fileStream.is_open()) {
			// Failed to open file
			return false;
		}

		std::string line;
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
				lineStream >> s1>>s2>>s3;
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
		}

		//file is now done loading, put it into a format that opengl can use
		std::vector<float> rawData; 
		for (int i = 0; i < faceIndicies.size(); i += 3)//+=3 because indicies are grouped in lots of 3
		{
			rawData.push_back(verticies[faceIndicies[i]-1].x);
			rawData.push_back(verticies[faceIndicies[i]-1].y);
			rawData.push_back(verticies[faceIndicies[i]-1].z);

			rawData.push_back(normals[faceIndicies[i + 2]-1].x);
			rawData.push_back(normals[faceIndicies[i + 2]-1].y);
			rawData.push_back(normals[faceIndicies[i + 2]-1].z);

			rawData.push_back(uv[faceIndicies[i + 1]-1].x);
			rawData.push_back(uv[faceIndicies[i + 1]-1].y);
		}


		IndexRawMeshData(rawData, data, indicies);
		return true;
	}

	static void IndexRawMeshData(const std::vector<float>& inData, std::vector<float>& vertexBufferData, std::vector<unsigned int>& indexBufferData)
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