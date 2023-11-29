#pragma once
#include <GL/glew.h>
#include <GLM/glm-master/glm/gtc/matrix_transform.hpp>
#include <GLM/glm-master/glm/glm.hpp>
#include <GLM/glm-master/glm/gtc/type_ptr.hpp>
#include <iostream>
#include "FileLoader.h"
class ShaderWrapper
{
private:
	int getUniformLocation(std::string name)
	{
        int location = glGetUniformLocation(Shader,  name.c_str());
		//if (location == -1)
			//std::cout << "uniform not found ("+(std::string)name+")"+"\n";
	
		return location;
	}
public:
    static unsigned int compileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            char* message = (char*)alloca(len * sizeof(char));
            glGetShaderInfoLog(id, len, &len, message);
            std::cout << "failed to compile shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message;
            glDeleteShader(id);
            return 0;
        }
        std::cout << "\nshader compiled succesfully id:" << id << " src:\n" << src << " END OF SHADER SRC \n";
        return id;
    }
    static int createShader(const std::string& vertexShader, const std::string& pixelShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, pixelShader);

        glAttachShader(program, vs); glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteProgram(vs); glDeleteShader(fs);

        return program;
    }
public:
	unsigned int Shader;
	void LoadShaders()
	{
		//create shaders
		std::string path = FileLoader::GetWorkingDir() + "/Source/Engine/Renderer/Shaders/";
        std::cout << "Path of shaders " + path << std::endl;
		std::string fragmentShader = FileLoader::GetFileContents(path + "defaultFragment.glsl");
		std::string vertexShader = FileLoader::GetFileContents(path + "defaultVertex.glsl");

		Shader = createShader(vertexShader, fragmentShader);
	}
    void SetSurfaceImage(int imageNumber,int slot)
    {
        std::string varName = "Texture_" + std::to_string(imageNumber);
        int location = getUniformLocation(varName);
        if (location != 0)
            glUniform1i(location, slot);
    }
	void UpdateMatricies(glm::mat4 projectionMatrix, glm::mat4 modelMatrix, glm::mat4 viewMatrix)
	{

        int location;
        
        location = getUniformLocation("V_ProjectionMatrix");
		if (location != -1)
		    glUniformMatrix4fv(location, 1, GL_FALSE,glm::value_ptr( projectionMatrix));

        location = getUniformLocation("F_ProjectionMatrix");
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



        location = getUniformLocation("V_ModelMatrix");
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

        location = getUniformLocation("F_ModelMatrix");
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));




        location = getUniformLocation("V_ViewMatrix");
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        location = getUniformLocation("F_ViewMatrix");
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
            
	}
};