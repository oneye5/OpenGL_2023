#pragma once

#include <iostream>
#include <vector>
#include "Camera.h"
#include "BufferManagement.h"

class Renderer
{
public:
    BufferManagement BufferManager;
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
