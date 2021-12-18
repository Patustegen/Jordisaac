#include "Singletons.h"
#define FPS 60

int main(int argc, char* args[]) {
	iVideo = Video::getInstance();
	iResourceM = ResourceManager::getInstance();
	iSoundM = SoundManager::getInstance();
	iAudio = Audio::getInstance();
	iInputM = InputManager::getInstance();
	iSceneD = SceneDirector::getInstance();

	unsigned int lastTime = 0, currentTime, deltaTime;
	float msFrame = 1 / (FPS / 1000.0f);

	while (true)
	{
		iVideo->clearScreen(0);

		iSceneD->getCurrentScene()->update();

		iSceneD->getCurrentScene()->render();

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
