#pragma once
#include "Systems.h"
class GameObject
{
public: 
	//for use by files inheriting GameObject
	bool Active = true;


	virtual void Start() = 0;
	virtual void Awake() = 0;
	virtual void Update(float ms) = 0;
};