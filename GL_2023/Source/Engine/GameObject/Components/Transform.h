#pragma once
#include "Component.h"
#include "GLM/glm-master/glm/glm.hpp"
#include <GLM/glm-master/glm/gtc/matrix_transform.hpp>
class Transform : public Component
{
    public:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
    glm::mat4 translationMatrix;

    
	glm::mat4 GetTranslationMatrix()
	{
        // Create transformation matrices for translation, rotation, and scaling
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pos);

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

        // Combine the transformation matrices to obtain the final transformation
        glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        return transformationMatrix;
	}
    virtual void UpdateComponent(float ms) override
    {
        if (pos != oldPos || rot != oldRot || scale != oldScale) //if translation matrix is dirty update it
        {
            translationMatrix = GetTranslationMatrix();
            oldPos = pos;
            oldRot = rot;
            oldScale = scale;
        }
    }

    virtual void OnDestroy() override
    {

    }


    Transform(GameObject* x) : Component(x) 
    {
        pos = glm::vec3(0);
        rot = glm::vec3(0);
        scale = glm::vec3(1);
        GetTranslationMatrix();
    };
   

private: 
    glm::vec3 oldPos; //used for detecting if current translation matrix is dirty
    glm::vec3 oldRot;
    glm::vec3 oldScale; 
};