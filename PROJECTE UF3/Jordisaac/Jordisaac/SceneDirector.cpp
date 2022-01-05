#include "SceneDirector.h"

#include "Portada.h"
#include "MainMenu.h"
#include "Game.h"
#include "OptionsMenu.h"
#include "Ranking.h"
#include "PauseMenu.h"
#include "ChooseCharacter.h"

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
	MainMenu	*mainM	= new MainMenu();
	Game	*game		= new Game();
	ChooseCharacter	*charac		= new ChooseCharacter();
	OptionsMenu	*options		= new OptionsMenu();
	Ranking	*rank		= new Ranking();
	PauseMenu	*pause	= new PauseMenu();

	mVectorScenes[PORTADA] = portada;
	mVectorScenes[MAIN] = mainM;
	mVectorScenes[GAME] = game;
	mVectorScenes[CHARACTER] = charac;
	mVectorScenes[OPTIONS] = options;
	mVectorScenes[RANK] = rank;
	mVectorScenes[PAUSE] = pause;

	portada->load();
	mainM->load();
	charac->load();

	mLastScene = PORTADA;
	mCurrScene = PORTADA;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit){
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}

void SceneDirector::changeLastScene(SceneEnum last_scene, bool reinit)
{
	mVectorScenes[last_scene]->setReInit(reinit);
	mLastScene = mCurrScene;
	mCurrScene = last_scene;
}
