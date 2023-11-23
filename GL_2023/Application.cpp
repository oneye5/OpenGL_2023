#include "Renderer.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Systems.h"

Renderer renderer;
InputManager inputManager;
GameObjectManager  objectManager;
int InitializeApplication()
{
	ENGINE_SYSTEMS::INPUT_CLASS = static_cast<void*>(&inputManager);
	ENGINE_SYSTEMS::RENDERER_CLASS = static_cast<void*>(&renderer);

	objectManager.init();
	return 0;
}
int ApplicationLoop()
{
	objectManager.UpdateObjects();
	return renderer.Render();

}
int main(void)
{
	InitializeApplication();
	while(ApplicationLoop()==0){}

	return 0;
}
