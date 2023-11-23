#include "GameObject.h"
#include <iostream>
#include "InputManager.h"
class testObject : public GameObject
{
public:
	virtual void Update(float ms) override
	{
		std::cout << "update "<<std::endl;
		auto x = ENGINE_SYSTEMS::GET_INPUTMANAGER();
		std::cout<<" w key pressed " << x->GetKey('w');
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