#pragma once

#include <iostream>
#include <vector>
#include "Camera.h"
#include "BufferManagement.h"

class Renderer
{

public:
    BufferManagement* BufferManager = new BufferManagement();
    Camera* ActiveCamera = nullptr;
    Renderer() : ActiveCamera(&ActiveCameraObject)
    {
       std::cout<<"Renderer initialized, code: "<< Initialize()<<std::endl;
    }
    int Initialize();
    int Render();
    void InitBuffers(std::vector<float> verticies, std::vector<unsigned int> indicies);

    void Destroy();

    int screenWidth = 1600;
    int screenHeight = 900;
    private: 
    Camera ActiveCameraObject = Camera(screenWidth, screenHeight);
    void RenderStatic();
    void RenderDynamic();





};
