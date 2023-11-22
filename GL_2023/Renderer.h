#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Renderer
{
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
    int Initialize();
    int Render();
    void InitBuffers(std::vector<float> verticies, std::vector<unsigned int> indicies);
    void Destroy();
};
