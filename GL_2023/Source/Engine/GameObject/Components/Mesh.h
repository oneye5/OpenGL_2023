#pragma once
//this component holds a mesh, that it sends to the renderer for rendering
#pragma once
#include "Component.h"
#include "GLM/glm-master/glm/glm.hpp"
#include <GLM/glm-master/glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

class Mesh : public Component
{
    std::vector<float> data;
    std::vector<unsigned int> indicies;
public:
    std::string MeshLocation;

    bool PushToRenderer(bool keepCopyOnStack);

    ///<summary><para>Loads the file and stores the data onto the stack, returns false if fails.</para><para> For example file == "mesh.obj"</para></summary>
    bool LoadFile(std::string file); 

    virtual void InitComponent() override
    {

    }

    virtual void UpdateComponent(float ms) override
    {
   
    }
};