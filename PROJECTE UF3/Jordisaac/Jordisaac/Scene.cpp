#include "Scene.h"
#include "Singletons.h"

Scene::Scene(){
	mReinit = true;
	alpha = 255;
	sID.resize(0);
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Menus/selectRight.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Menus/selectLeft.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Menus/pageTurn.mp3"));
	sID.push_back(iSoundM->loadAndGetSoundID("Assets/Music/intro-theme.mp3"));
}

Scene::~Scene(){
}

void Scene::init(){
	mReinit = false;
}

void Scene::reinit(){
	mReinit = true;
}
