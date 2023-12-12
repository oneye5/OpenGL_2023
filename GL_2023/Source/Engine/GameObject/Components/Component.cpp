#include "Component.h"
#include "iostream"
#include "GameObject.h"

Component::Component(GameObject* obj)
{
	std::cout << "initializing component, component.cpp";
	obj->AddComponent(this);
}
