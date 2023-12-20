#pragma once
#include <GL/glew.h>
#include <GLM/glm-master/glm/gtc/matrix_transform.hpp>
#include <GLM/glm-master/glm/glm.hpp>
#include <GLM/glm-master/glm/gtc/type_ptr.hpp>




class Camera
{
public:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f);

	glm::vec3 front;
	glm::vec3 up;

	int& screenWidth;
	int& screenHeight;
	const float nearPlane = 0.001f;
	const float farPlane = 1000.0f;
	const float fov = 100.0f;
	
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;


	glm::vec3 rayFromAngle(glm::vec3 A)
	{
		// Convert degrees to radians
		float yaw = glm::radians(A.y);
		float pitch = glm::radians(A.x);
		float x, y, z;
		x = sinf(yaw) * cosf(pitch);
		y = sinf(pitch);
		z = cosf(yaw) * cosf(pitch);

		return  glm::vec3(x, y, z);
	}

	void makeView() 
	{
		viewMatrix = glm::lookAt(pos, pos + front, up);
	}
	void makeProjectionMatrix()
	{
		projectionMatrix = glm::perspective(glm::radians(fov),(float)screenWidth /(float)screenHeight,nearPlane,farPlane);
	}
	void updateRotation()
	{
		front = rayFromAngle(rot);
		// Calculate a temporary right vector perpendicular to the front and the world up vector
		glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		up = glm::normalize(glm::cross(right, front));
	}
	Camera(int& w, int& h) : screenWidth(w),screenHeight(h)
	{
		updateRotation();
		makeView();
		makeProjectionMatrix();
	}
};