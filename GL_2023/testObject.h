#include "GameObject.h"
#include <iostream>
#include "InputManager.h"
#include "Renderer.h"
class testObject : public GameObject
{
public:
	virtual void Update(float ms) override
	{
		auto Inputs = ENGINE_SYSTEMS::GET_INPUTMANAGER();
		auto renderer = ENGINE_SYSTEMS::GET_RENDERER();
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

		xRot *= -3.0f; yRot *= -3.0f;

		renderer->ActiveCamera->rot += glm::vec3(yRot, xRot, 0.0f);
	}
	virtual void Awake() override
	{
		std::cout << "awake" << std::endl;
	}
	virtual void Start() override
	{
		std::cout << "start"<< std::endl;
	}
};