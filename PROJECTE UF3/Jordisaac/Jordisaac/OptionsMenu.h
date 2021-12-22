#pragma once
#include "Scene.h"

enum sOption {CONTROLS, SFX, MUSIC, GAMMA};

class OptionsMenu :
    public Scene
{
public:
	//! Handles the drawing of the scene
	void render();

	//! Handles the updating of the scene
	void update();

	//! Loads Scene Assets.
	void load();
private:
	sOption selected;
};

