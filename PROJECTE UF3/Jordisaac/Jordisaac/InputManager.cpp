#include "InputManager.h"
#include <iostream>
#include <stdio.h>

InputManager* InputManager::pInstance = NULL;

InputManager::InputManager()
{
	controller = nullptr;
	focus = SDL_TRUE;
	for (int i = 0; i < INPUTLENGHT; i++)
	{
		events[i] = false;
	}
	test_event = new SDL_Event();
}

InputManager::~InputManager()
{
}

void InputManager::openController()
{
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				break;
			}
			else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}
}

void InputManager::getInput()
{
	while (SDL_PollEvent(test_event))
	{
		if (test_event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		{
			focus = SDL_FALSE;
		}
		else if (test_event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		{
			focus = SDL_TRUE;
		}
		if (focus)
		{
			switch (test_event->type) {
			case SDL_QUIT:
				SDL_Log("Program quit after %i ticks", test_event->quit.timestamp);
				SDL_Quit();
				break;
			case SDL_KEYUP:
				if (test_event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					events[QUIT] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					events[SHOOTLEFT] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					events[SHOOTRIGHT] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_UP)
				{
					events[SHOOTUP] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					events[SHOOTDOWN] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_W)
				{
					events[GOUP] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_S)
				{
					events[GODOWN] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_A)
				{
					events[GOLEFT] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_D)
				{
					events[GORIGHT] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					events[USEITEM] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_Q)
				{
					events[USECONS] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_E)
				{
					events[USEBOMB] = false;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					events[ENTER] = false;
				}
				break;
			case SDL_KEYDOWN:
				if (test_event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					events[QUIT] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					events[SHOOTLEFT] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					events[SHOOTRIGHT] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_UP)
				{
					events[SHOOTUP] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					events[SHOOTDOWN] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_W)
				{
					events[GOUP] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_S)
				{
					events[GODOWN] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_A)
				{
					events[GOLEFT] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_D)
				{
					events[GORIGHT] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					events[USEITEM] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_Q)
				{
					events[USECONS] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_E)
				{
					events[USEBOMB] = true;
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					events[ENTER] = true;
				}
				break;
			}
		}
	}
}
