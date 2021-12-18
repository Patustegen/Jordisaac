#include "SceneDirector.h"

#include "Portada.h"
#include "MainMenu.h"
#include "Game.h"
#include "OptionsMenu.h"
#include "Ranking.h"
#include "PauseMenu.h"

SceneDirector* SceneDirector::pInstance = NULL;

SceneDirector* SceneDirector::getInstance(){
	if (!pInstance) {
		pInstance = new SceneDirector();
	}
	return pInstance;
}

SceneDirector::SceneDirector(){
	init();
}

SceneDirector::~SceneDirector(){
}

void SceneDirector::init(){
	mVectorScenes.resize(NUM_SCENES);

	Portada	*portada		= new Portada();
	MainMenu	*main	= new MainMenu();
	Game	*game		= new Game();
	OptionsMenu	*options		= new OptionsMenu();
	Ranking	*rank		= new Ranking();
	PauseMenu	*pause	= new PauseMenu();

	mVectorScenes[PORTADA] = portada;

	portada->load();

	mCurrScene = PORTADA;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit){
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}
