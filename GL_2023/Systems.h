#pragma once
//this is used to expose gameobjects to the core systems of the engine without creating dependency or memory issues
class Renderer;
class InputManager;
static struct ENGINE_SYSTEMS
{
	static void* RENDERER_CLASS;
	static void* INPUT_CLASS;

	static Renderer* GET_RENDERER();
	static InputManager* GET_INPUTMANAGER();
};