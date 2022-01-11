#include "Singletons.h"

int main(int argc, char* args[]) {
	iVideo = Video::getInstance();
	iResourceM = ResourceManager::getInstance();
	iSoundM = SoundManager::getInstance();
	iAudio = Audio::getInstance();
	iInputM = InputManager::getInstance();
	iSceneD = SceneDirector::getInstance();

	

	iSceneD->getCurrentScene()->init();
	while (true)
	{
		iVideo->clearScreen(0);

		iInputM->getInput();
		iSceneD->getCurrentScene()->update();

		iSceneD->getCurrentScene()->render();

		iVideo->updateScreen();
		iVideo->updateTime();
	}

	return 0;
}
