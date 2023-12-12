#pragma once
//this component holds a mesh, that it sends to the renderer for rendering
#pragma once
#include "Component.h"
#include "GLM/glm-master/glm/glm.hpp"
#include <GLM/glm-master/glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "Renderer.h"
#include "Transform.h"

class Mesh : public Component
{

    Transform* assosiatedTransform = nullptr;
    std::vector<float> data;
    std::vector<std::vector<unsigned int>> indicies;
public:
    std::vector<unsigned int> TextureSlots;
    std::string MeshLocation;
    bool Static;
    bool PushToBuffer();
    Mesh(GameObject* gameObject,std::string meshPath) : Component(gameObject) {};
    
    ///<summary><para>Loads the file and stores the data onto the stack, returns false if fails.</para><para> For example file == "mesh.obj"</para></summary>
    bool LoadFile(std::string file); 

    virtual void InitComponent() override
    {

    }

    virtual void UpdateComponent(float ms) override
    {
   
    }

    virtual void OnDestroy() override
    {

    }
};