#pragma once
#include "Systems.h"
#include "Component.h"
#include "vector"
class GameObject
{
private:
	std::vector<Component*> Components;
public: 
	//for use by files inheriting GameObject
	bool Active = true;
	
	void AddComponent(Component* c)
	{
		
		if (c == nullptr)
		{
			std::cout << "Error adding compent, argument was nullptr in GameObject.h";
		}
		
		Components.push_back(c);
		c->parentObject = this;
	
	}
	void DestroyComponent(Component* c)
	{
		c->OnDestroy();

		auto iterator = std::find(Components.begin(), Components.end(), c);
		if (iterator != Components.end()) {
			delete* iterator; 
			Components.erase(iterator);
		}
	}
	void UpdateComponents(float ms)
	{
		for (auto x : Components)
			x->UpdateComponent(ms);
	}
	virtual void Start() = 0;
	virtual void Awake() = 0;
	virtual void Update(float ms) = 0;
};