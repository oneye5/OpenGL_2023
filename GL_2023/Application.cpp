#include<iostream>
#include "Renderer.h"
#include <vector>



//program components
Renderer renderer;
int InitializeApplication()
{
	
	return renderer.Initialize();;
}
int ApplicationLoop()
{

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
