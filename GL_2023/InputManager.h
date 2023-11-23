#pragma once
#include <windows.h>  
#include<unordered_map>
#include <string>
#include<GLM/glm-master/glm/glm.hpp>

#define SPACEBAR '&'
#define ESCAPE '*'
#define CONTROL '('
#define SHIFT ')'
#define TAB '_'
#define ALT '+'
#define RIGHT_ARROW '^'
#define LEFT_ARROW '%'
#define UP_ARROW '$'
#define DOWN_ARROW '#'

class InputManager
{
private:
	std::unordered_map<char, bool> keyStates;
public:
	
	
	void Tick() //update all key states
	{
		for (char i = 'a'; i <= 'z'; i++) 
			keyStates[i] = (GetKeyState(i) < 0);
		
		for (char i = '0'; i <= '9'; i++) 
			keyStates[i] = (GetKeyState(i) < 0);
		//special chars
		keyStates[SPACEBAR] = (GetKeyState(VK_SPACE) < 0);
		keyStates[ESCAPE] = (GetKeyState(VK_ESCAPE) < 0);
		keyStates[CONTROL] = (GetKeyState(VK_CONTROL) < 0);
		keyStates[SHIFT] = (GetKeyState(VK_SHIFT) < 0);
		keyStates[TAB] = (GetKeyState(VK_TAB) < 0);
		keyStates[ALT] = (GetKeyState(VK_MENU) < 0);
		keyStates[RIGHT_ARROW] = (GetKeyState(VK_RIGHT) < 0);
		keyStates[LEFT_ARROW] = (GetKeyState(VK_LEFT) < 0);
		keyStates[UP_ARROW] = (GetKeyState(VK_UP) < 0);
		keyStates[DOWN_ARROW] = (GetKeyState(VK_DOWN) < 0);
	}

	bool RecheckKey(char key) //used for time sensitive tasks to avoid any input lag
	{
		bool out = (GetKeyState(key) < 0);
		keyStates[key] = out;
		return out;
	}

	bool GetKey(char key)
	{
		return keyStates[key];
	}	
	glm::vec3 GetNormalizedMove()
	{
		auto moveV = GetMoveVector();
		glm::vec2 normalized = glm::vec2(moveV.x, moveV.z);
		normalized = glm::normalize(normalized);
		moveV.x = normalized.x; moveV.z = normalized.y;
		return moveV;
	}
	glm::vec3 GetMoveVector()
	{
		auto out = glm::vec3(0.0f);

		if (GetKey(UP_ARROW) || GetKey('w'))
			out.z++;

		if (GetKey(DOWN_ARROW || GetKey('s')))
			out.z--;

		if (GetKey(RIGHT_ARROW) || GetKey('d'))
			out.x++;

		if (GetKey(LEFT_ARROW) || GetKey('a'))
			out.x--;

		if (GetKey(SPACEBAR))
			out.y++;
		
		if (GetKey(CONTROL))
			out.y--;

		return out;
	}

	
};