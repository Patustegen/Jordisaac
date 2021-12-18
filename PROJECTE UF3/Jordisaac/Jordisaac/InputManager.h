#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>

enum inputs { QUIT, GOUP, GORIGHT, GODOWN, GOLEFT, SHOOTUP, SHOOTRIGHT, SHOOTDOWN, SHOOTLEFT, USEBOMB, USEITEM, USECONS };

class InputManager
{
	static InputManager* pInstance;
	SDL_Event test_event;
	SDL_GameController* controller;
	bool focus;
	std::vector<inputs> events;
protected:
	InputManager();
public:
	~InputManager();
	void openController();
	std::vector<inputs> getInput();
	static InputManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new InputManager();
		return pInstance;
	}
};

