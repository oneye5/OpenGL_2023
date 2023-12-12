#pragma once
#include <vector>
#include "GameObject.h"
/*
			IMPORTANT NOTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			ALL GAMEOBJECT CLASSES MUST BE INCLUDED IN THIS FILE, AS WELL AS ADDED TO "INSTANCIATE ON RUN" METHOD
*/
#pragma region gameObject class includes
#include "testObject.h"
#pragma endregion
class GameObjectManager
{
public:

	std::vector<GameObject*> GameObjects;
	void AddObject(GameObject* obj)
	{
		GameObjects.push_back(obj);
		obj->Awake();
	}

	
	void UpdateObjects()
	{
		for (auto obj : GameObjects)
		{
			if (obj->Active)
			{
				obj->Update(-1.0f);//not yet properly implimented
				obj->UpdateComponents(-1.0f); 
			}
		}
	}

	void init()
	{
		InstanciateObjectsOnRun();
		for (auto obj : GameObjects)
		{
			obj->Start();
		}
	}
private:
	
	std::vector<GameObject*> ToCallAwakeIndex;	
	
	void InstanciateObjectsOnRun() 
	{
		//Include all gameobjects here also ! ===========================================================================
		AddObject(new testObject());
	}

	
	

};