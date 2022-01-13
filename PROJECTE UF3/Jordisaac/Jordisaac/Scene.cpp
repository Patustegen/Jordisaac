#include "Scene.h"

Scene::Scene(){
	mReinit = true;
	alpha = 255;
}

Scene::~Scene(){
}

void Scene::init(){
	mReinit = false;
}

void Scene::reinit(){
	mReinit = true;
}
