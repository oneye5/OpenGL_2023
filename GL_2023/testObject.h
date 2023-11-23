#include "GameObject.h"
#include <iostream>
class testObject : public GameObject
{
public:
	virtual void Update(float ms) override
	{
		std::cout << "update"<<std::endl;
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