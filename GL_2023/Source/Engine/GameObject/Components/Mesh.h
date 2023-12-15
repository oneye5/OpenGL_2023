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
#include "FileLoader.h"

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

    /// <summary>
    /// loads mesh data and stores it into the mesh component, the file path is relative to the mesh file, so for example file == "mesh.obj"
    /// </summary>
    Mesh(GameObject* gameObject,Transform* transform,std::string meshPath,vector<unsigned int> textureSlots, bool isStaticObject) : Component(gameObject) 
    {
        LoadFile(meshPath);
        Static = isStaticObject;
        TextureSlots = textureSlots;
        assosiatedTransform = transform;
    };
    
    ///<summary><para>Loads the file and stores the data onto the stack, returns false if fails.</para><para> For example file == "mesh.obj"</para></summary>
    bool LoadFile(std::string file); 

    

    virtual void UpdateComponent(float ms) override
    {
   
    }

    virtual void OnDestroy() override
    {

    }
};