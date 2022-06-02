#pragma once
#include "Scene.h"
class Ranking :
    public Scene
{
public:
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();

	void init();
private:
	int gNums;
	int gCharac;
	int rPlayer[10];
	int rScore[10];
};

