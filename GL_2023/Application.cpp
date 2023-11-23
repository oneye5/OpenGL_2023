#include<iostream>
#include "Renderer.h"
#include "GameObjectManager.h"
#include <vector>
#include "InputManager.h"

//This file contains the main function, it calls initialization methods and update for all the important systems


//program components
Renderer renderer;
InputManager inputManager;
GameObjectManager  objectManager(&renderer,&inputManager);
int InitializeApplication()
{
	

	return 0;
}
int ApplicationLoop()
{
	objectManager.UpdateObjects();
	return renderer.Render();
}

int main(void)
{

	if (InitializeApplication() != 0)
	{
		std::cout << "failed to initialize (Application)";
		return -1;
	}
	while(ApplicationLoop()==0){}

	return 0;
}
 