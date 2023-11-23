#include "Systems.h"
#include "Renderer.h"
#include "InputManager.h"
void* ENGINE_SYSTEMS::RENDERER_CLASS = nullptr;
void* ENGINE_SYSTEMS::INPUT_CLASS = nullptr;

Renderer* ENGINE_SYSTEMS::GET_RENDERER()
{
	return static_cast<Renderer*>(RENDERER_CLASS);
}
InputManager* ENGINE_SYSTEMS::GET_INPUTMANAGER()
{
	return static_cast<InputManager*>(INPUT_CLASS);
}