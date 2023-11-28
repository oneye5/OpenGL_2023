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