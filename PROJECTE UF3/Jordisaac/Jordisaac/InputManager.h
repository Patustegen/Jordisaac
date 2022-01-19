#pragma once
#include "SDL.h"

enum inputs { QUIT, GOUP, GORIGHT, GODOWN, GOLEFT, SHOOTUP, SHOOTRIGHT, SHOOTDOWN, SHOOTLEFT, USEBOMB, USEITEM, USECONS, ENTER,
INPUTLENGHT};

class InputManager
{
	static InputManager* pInstance;
	SDL_Event* test_event;
	SDL_GameController* controller;
	bool focus;
	bool events[INPUTLENGHT];
	bool gameMode;
protected:
	InputManager();
public:
	~InputManager();
	void openController();
	void getInput();
	bool getEvents(inputs input) { return events[input]; };
	void switchGameMode(bool gm) { gameMode = gm; };
	static InputManager* getInstance()
	{
		if (pInstance == NULL) pInstance = new InputManager();
		return pInstance;
	}
};

