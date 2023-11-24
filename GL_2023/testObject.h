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
		renderer->ActiveCamera->pos += moveBy;
		std::cout << "currnet cam pos " << renderer->ActiveCamera->pos.x << " " << renderer->ActiveCamera->pos.y << " " << renderer->ActiveCamera->pos.z << std::endl;

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