#pragma once
//this component holds a mesh, that it sends to the renderer for rendering
#pragma once
#include "Component.h"
#include "GLM/glm-master/glm/glm.hpp"
#include <GLM/glm-master/glm/gtc/matrix_transform.hpp>
class Mesh : public Component
{
public:
    virtual void InitComponent() override
    {

    }

    virtual void UpdateComponent(float ms) override
    {
   
    }
};