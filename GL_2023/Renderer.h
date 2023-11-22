#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Renderer
{
public:
    int Initialize();
    int Render();
    void InitBuffers(std::vector<float> verticies, std::vector<unsigned int> indicies);
    void Destroy();
};
