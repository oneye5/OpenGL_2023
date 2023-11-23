#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Camera.h"

class Renderer
{
public:

    Camera* ActiveCamera;
    Renderer()
    {
       std::cout<<"Renderer initialized, code: "<< Initialize()<<std::endl;
    }
    int Initialize();
    int Render();
    void InitBuffers(std::vector<float> verticies, std::vector<unsigned int> indicies);
    void Destroy();
};
