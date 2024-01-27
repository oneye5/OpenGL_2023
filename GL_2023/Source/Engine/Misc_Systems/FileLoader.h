#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <direct.h>
#include <stb_image.h>
#include <array>
#include "unordered_map"
#include <set>


using std::string;
using std::vector;
static class FileLoader
{
public:
	static int removeDecimal(float number)
	{
		// Multiply the float by a power of 10 to shift the decimal point
		float shiftedNumber = number * 10000.0f; // 4.4444 * 10000 = 44444.4

		// Cast the result to an integer
		int result = static_cast<int>(shiftedNumber);

		return result;
	}
	static bool LoadMeshV3(std::string path, std::vector<float>& dataOut, std::vector<std::vector<unsigned int>>& indiciesOut)
	{
		dataOut.clear(); indiciesOut.clear();
		std::vector<glm::vec3> verticies, normals; std::vector<glm::vec2> uv;
		std::vector<std::vector<unsigned int>> faceIndiciesGroups;

#pragma region loadfile

		std::ifstream fileStream(path);
		if (!fileStream.is_open()) {
			std::cout << "failed to open file in loadmesh";
			return false;
		}

		{
			std::string line; std::vector<unsigned int> faceIndicies;
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
		}
#pragma endregion
#pragma region removeIndexBuffer
		//group,vertex,vertexcomponents,component
		vector<vector<vector<float>>> indexlessData;
		for (auto& group : faceIndiciesGroups)
		{
			vector<vector<float>> groupData;
				
			for (int i = 0; i < group.size();)
			{
				
				vector<float> vData;
				vData.push_back(verticies[group[i] - 1].x);
				vData.push_back(verticies[group[i] - 1].y);
				vData.push_back(verticies[group[i] - 1].z); i++;



				vData.push_back(uv[group[i] - 1].x);
				vData.push_back(uv[group[i] - 1].y); i++;

				vData.push_back(normals[group[i] - 1].x);
				vData.push_back(normals[group[i] - 1].y);
				vData.push_back(normals[group[i] - 1].z); i++;

				groupData.push_back(vData);
			}
			indexlessData.push_back(groupData);
			
		}
#pragma endregion
#pragma region reformatting

#pragma endregion

			return false;
	}
	static bool LoadMeshV2(std::string path, std::vector<float>& dataOut, std::vector<std::vector<unsigned int>>& indiciesOut)
	{
		struct VertexData
		{
			float x, y, z, nx, ny, nz, u, v;

			std::array<float, 8> getComponents() const
			{
				return std::array<float, 8>{x, y, z, nx, ny, nz, u, v};
			}

			int getProduct() const
			{
				return removeDecimal(x) + removeDecimal(y) * 10 + removeDecimal(z) * 100 + removeDecimal(nx) * 1000 +
					removeDecimal(ny) * 10000 + removeDecimal(nz) * 100000 + removeDecimal(u) * 1000000 + removeDecimal(v) * 10000000;
			}
		};

		dataOut.clear(); indiciesOut.clear();

		std::vector<glm::vec3> verticies, normals; std::vector<glm::vec2> uv;
		std::vector<std::vector<unsigned int>> faceIndiciesGroups;


		std::ifstream fileStream(path);
		if (!fileStream.is_open()) {
			std::cout << "failed to open file in loadmesh";
			return false;
		}

		{
			std::string line; std::vector<unsigned int> faceIndicies;
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
		}


		//debug
		std::cout << std::endl;
		for (auto x : faceIndiciesGroups)
			for (auto y : x)
			{
				std::cout << y << " ";
			}



		//file is now done loading, put it into a format that opengl can use
		//get rid of index buffer to recreate an opengl compatible one later

		vector<vector<VertexData>> processedVertexData;
		for (auto group : faceIndiciesGroups) //formatted as xyz uv and normal xyz
		{
			vector<VertexData> groupData;

			for (int i = 0; i < group.size();)
			{
				VertexData vData;
				vData.x = verticies[group[i] - 1].x;
				vData.y = verticies[group[i] - 1].y;
				vData.z = verticies[group[i] - 1].z; i++;

			

				vData.u = uv[group[i] - 1].x;
				vData.v = uv[group[i] - 1].y;i++;
				
				vData.nx = normals[group[i] - 1].x;
				vData.ny = normals[group[i] - 1].y;
				vData.nz = normals[group[i] - 1].z; i++;

				groupData.push_back(vData);
			}
			processedVertexData.push_back(groupData);
		}
		


		

		std::vector<float> vertexBuffer;
		std::vector<std::vector<unsigned int>> indicesBuffers;

		// Combine the vertices and generate index buffers for each material group
		for (const auto& group : processedVertexData) {
			std::unordered_map<int, unsigned int> indexMap; // Map to keep track of vertices

			// Generate a new index buffer for this material group
			std::vector<unsigned int> indices;

			// Process each vertex in the group
			for (const auto& vertex : group) {
				int vertexHash = vertex.getProduct(); // Assuming getProduct() gives a unique hash for a VertexData
				auto it = indexMap.find(vertexHash);

				if (it != indexMap.end()) {
					// Vertex already exists, add its index to indices buffer
					indices.push_back(it->second);
				}
				else {
					// New vertex, add it to the vertex buffer and update the index buffer
					//vertexBuffer.insert(vertexBuffer.end(), vertex.getComponents().begin(), vertex.getComponents().end());
					for (auto& x : vertex.getComponents())
						vertexBuffer.push_back(x);

					unsigned int newIndex = static_cast<unsigned int>((vertexBuffer.size() / 8) - 1); // New index
					indices.push_back(newIndex); // Add index to buffer
					indexMap[vertexHash] = newIndex; // Update map with the new index
				}
			}

			// Store the indices buffer for this material group
			indicesBuffers.push_back(indices);
		}

		// Finally, assign the data to the output parameters
		dataOut = std::move(vertexBuffer);
		indiciesOut = std::move(indicesBuffers);



		return true;
	}

	/// <summary>
	/// Loads a specified .obj file using a full path and reformats and indexes the data for use by OpenGL. use GetWorkingDir() to make it relative to the project.
	/// </summary>
	/// <param name="data">Used as an output. Adds data for the verticies, including positon, normal and uv data.</param>
	/// <param name="indicies">Used as an output. Each index refers to a set of vertex data.</param>
	/// <returns>Returns false if the method fails.</returns>
	static bool LoadMesh(std::string path, std::vector<float>& dataOut, std::vector<std::vector<unsigned int>>& indiciesOut)
	{
		return LoadMeshV2(path, dataOut, indiciesOut);
		struct VertexData
		{

			float x, y, z, nx, ny, nz, u, v;

			std::array<float, 8> getComponents() const
			{
				return std::array<float, 8>{x, y, z, nx, ny, nz, u, v};
			}

			int getProduct() const
			{
				return removeDecimal(x) + removeDecimal(y) * 10 + removeDecimal(z) * 100 + removeDecimal(nx) * 1000 +
					removeDecimal(ny) * 10000 + removeDecimal(nz) * 100000 + removeDecimal(u) * 1000000 + removeDecimal(v) * 10000000;
			}
		};

		dataOut.clear(); indiciesOut.clear();

		std::vector<glm::vec3> verticies, normals; std::vector<glm::vec2> uv;
		std::vector<std::vector<unsigned int>> faceIndiciesGroups;


		std::ifstream fileStream(path);
		if (!fileStream.is_open()) {
			std::cout << "failed to open file in loadmesh";
			return false;
		}

		std::string line; std::vector<unsigned int> faceIndicies;
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
		
		//debug
		std::cout<<std::endl;
		for (auto x : faceIndiciesGroups)
			for (auto y : x)
			{
				std::cout << y << " ";
			}



		//file is now done loading, put it into a format that opengl can use
		


		//get rid of index buffer to recreate an opengl compatible one later
			



		vector<vector<VertexData>> objectDataGroups; 
		
		for (auto faceIndicies2 : faceIndiciesGroups)
		{
			vector<VertexData> dataGroup;
			for (int i = 0; i < faceIndicies2.size(); i += 3)//+=3 because indicies are grouped in lots of 3
			{
				VertexData vData;	
				vData.x = (verticies[faceIndicies2[i] - 1].x);
				vData.y = (verticies[faceIndicies2[i] - 1].y);
				vData.z = (verticies[faceIndicies2[i] - 1].z);

				vData.nx = (normals[faceIndicies2[i + 2] - 1].x);
				vData.ny = (normals[faceIndicies2[i + 2] - 1].y);
				vData.nz = (normals[faceIndicies2[i + 2] - 1].z);

				vData.u = (uv[faceIndicies2[i + 1] - 1].x);
				vData.v = (uv[faceIndicies2[i + 1] - 1].y);

				std::cout << vData.x << " " << vData.y << " " << vData.z << " " << vData.nx << " " << vData.ny << " " << vData.nz << " " << vData.u << " " << vData.v <<std::endl;

	 			dataGroup.push_back(vData);
			}
			objectDataGroups.push_back(dataGroup);
		}
	
		//now put in one vertex buffer and generate new index buffers per object group / texture


		
		std::unordered_map<int , unsigned int> elements;
		vector<VertexData> vertexData;
		for (vector<VertexData> objectData : objectDataGroups)
		{ 
			vector<unsigned > groupIndecies;
			for (VertexData vertex : objectData)
			{ 
				unsigned int index = -1;
				auto iterator = elements.find(vertex.getProduct());

				if (iterator != elements.end()) //element found
				{
					index = iterator->second; 
					///std::cout << "duplicate item found, indexing approrocately" << std::endl;
				}
				else
				{
					vertexData.push_back(vertex);
					index = vertexData.size() - 1;
					elements.insert(std::make_pair(vertex.getProduct(), index));

					//std::cout << "no duplicate element found" << std::endl;
				}

				groupIndecies.push_back(index);
			}
			
			indiciesOut.push_back(groupIndecies);
		}
	


		for (auto& data : vertexData)
		{
			dataOut.push_back(data.x);
			dataOut.push_back(data.y);
			dataOut.push_back(data.z);

			dataOut.push_back(data.nx);
			dataOut.push_back(data.ny);
			dataOut.push_back(data.nz);

			dataOut.push_back(data.u);
			dataOut.push_back(data.v);
		}
		

		//debug 
		for (auto group : indiciesOut)
		{
			for (auto x : group)
			{
				std::cout << 
					dataOut[x * 8]     << " " << dataOut[x * 8 + 1] << " " <<
					dataOut[x * 8 + 2] << " " << dataOut[x * 8 + 3] << " " <<
					dataOut[x * 8 + 4] << " " << dataOut[x * 8 + 5] << " " <<
					dataOut[x * 8 + 6] << " " << dataOut[x * 8 + 7] << std::endl;
			}
		}
		

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