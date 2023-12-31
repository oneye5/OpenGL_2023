#include "GameObject.h"
#include <iostream>
#include "InputManager.h"
#include "Renderer.h"

#include "Transform.h"
#include "Mesh.h";
#include "FileLoader.h"
class testObject : public GameObject
{
	Mesh* mesh = nullptr;
	Transform* transform = nullptr;
	Renderer* renderer = nullptr;
	InputManager* Inputs = nullptr;
public:
	virtual void Update(float ms) override
	{

		auto moveBy = Inputs->GetMoveVector();
		renderer->ActiveCamera->pos += moveBy/500.0f;
		std::cout << "currnet cam pos " << renderer->ActiveCamera->pos.x << " " << renderer->ActiveCamera->pos.y << " " << renderer->ActiveCamera->pos.z << std::endl;
		
		float xRot =0, yRot=0;
		if (Inputs->GetKey('E'))
			xRot += 0.01;
		if (Inputs->GetKey('Q'))
			xRot -= 0.01;
		if (Inputs->GetKey('R'))
			yRot += 0.01;
		if (Inputs->GetKey('T'))
			yRot -= 0.01;

		xRot *= -10.0f; yRot *= -10.0f;

		renderer->ActiveCamera->rot += glm::vec3(yRot, xRot, 0.0f);

		
	}
	virtual void Awake() override
	{
		std::cout << "awake" << std::endl;
	}
	virtual void Start() override
	{
		std::cout << "start"<< std::endl;

		Inputs = ENGINE_SYSTEMS::GET_INPUTMANAGER();
		renderer = ENGINE_SYSTEMS::GET_RENDERER();

		transform = new Transform(this);
		std::vector<unsigned int> textureSlots; textureSlots.push_back(0);
		mesh = new Mesh(this, transform, "untitled.obj", textureSlots, false);
		mesh->PushToBuffer();
		renderer->BufferManager->RefreshIndexBuffer();
		renderer->InitBuffers(renderer->BufferManager->vertexBuffer, renderer->BufferManager->indexBuffer);
	}
};