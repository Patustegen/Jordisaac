#include "InputManager.h"

InputManager* InputManager::pInstance = NULL;

InputManager::InputManager()
{
	controller = nullptr;
	focus = SDL_TRUE;
	events.resize(0);
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
	events.resize(0);
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
				if (test_event->key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					events.push_back(STOPSLEFT);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					events.push_back(STOPSRIGHT);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_UP)
				{
					events.push_back(STOPSUP);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					events.push_back(STOPSDOWN);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_W)
				{
					events.push_back(STOPUP);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_S)
				{
					events.push_back(STOPDOWN);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_A)
				{
					events.push_back(STOPLEFT);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_D)
				{
					events.push_back(STOPRIGHT);
				}
				break;
			case SDL_KEYDOWN:
				if (test_event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					events.push_back(QUIT);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					events.push_back(SHOOTLEFT);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					events.push_back(SHOOTRIGHT);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_UP)
				{
					events.push_back(SHOOTUP);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					events.push_back(SHOOTDOWN);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_W)
				{
					events.push_back(GOUP);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_S)
				{
					events.push_back(GODOWN);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_A)
				{
					events.push_back(GOLEFT);
				}
				else if (test_event->key.keysym.scancode == SDL_SCANCODE_D)
				{
					events.push_back(GORIGHT);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					events.push_back(USEITEM);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_Q)
				{
					events.push_back(USECONS);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_E)
				{
					events.push_back(USEBOMB);
				}

				if (test_event->key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					events.push_back(ENTER);
				}
				break;
			}
		}
	}
}
