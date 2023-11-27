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
		Components.push_back(c);
		c->InitComponent();
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