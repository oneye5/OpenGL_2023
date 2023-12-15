#pragma once
class GameObject;
class Component
{
private:

public:
	//for use by files inheriting component
	bool Active = true;
	void* parentObject = nullptr; //GameObject type

	virtual void UpdateComponent(float ms) = 0;
	virtual void OnDestroy() = 0;
	Component(GameObject* gameObject);
};

