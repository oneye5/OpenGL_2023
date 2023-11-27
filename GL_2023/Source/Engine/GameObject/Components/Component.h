#pragma once

class Component
{
public:
	//for use by files inheriting component
	class GameObject;
	bool Active = true;
	GameObject* parentObject = nullptr;
	virtual void InitComponent() = 0;
	virtual void UpdateComponent(float ms) = 0;
	virtual void OnDestroy() = 0;
};