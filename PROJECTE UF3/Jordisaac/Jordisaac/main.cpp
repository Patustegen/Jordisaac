#include "Singletons.h"
#define FPS 60

void cargaImatges();

int main(int argc, char* args[]) {
	iVideo = Video::getInstance();
	iResourceM = ResourceManager::getInstance();
	iSoundM = SoundManager::getInstance();
	iAudio = Audio::getInstance();
	iInputM = InputManager::getInstance();
	iSceneD = SceneDirector::getInstance();

	unsigned int lastTime = 0, currentTime, deltaTime;
	float msFrame = 1 / (FPS / 1000.0f);

	int alpha = 0;
	int menus[2];
	menus[0] = iResourceM->loadAndGetGraphicID("Assets\\Menus\\splashmenu.png");
	menus[1] = iResourceM->loadAndGetGraphicID("Assets\\Menus\\mainmenu.png");

	while (true)
	{
		iVideo->clearScreen(0);

		iResourceM->setAlphaGraphic(menus[0], alpha);
		iVideo->renderGraphic(menus[0], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (alpha < 255)
		{
			if (alpha > 150)
			{
				alpha += 7;
			}
			else
			{
				alpha+= 2;
			}
		}
		if (alpha > 255)
		{
			alpha = 255;
		}

		iVideo->updateScreen();
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		if (deltaTime < (int)msFrame) {
			iVideo->waitTime((int)msFrame - deltaTime);
		}
		lastTime = currentTime;
	}

	return 0;
}

void cargaImatges()
{
	
}
