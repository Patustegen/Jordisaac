#pragma once
#include "Scene.h"

enum selected
{
	NEWGAME, CONTINUE, S_RANKING, STATS, S_OPTIONS
};

class MainMenu :
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

	MainMenu();
	~MainMenu();
private:
	int bgImage;
	int selector;
	selected menuSelected;
};

