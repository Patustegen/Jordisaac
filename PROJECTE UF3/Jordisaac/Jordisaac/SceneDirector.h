#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <vector>
#include "Scene.h"
#include "enums.h"

//! Enum Scenes.
/*! All the Scenes in the game. */
enum SceneEnum {
		PORTADA, MAIN, CHARACTER, GAME, OPTIONS, RANK, PAUSE, GAME_OVER,
		_LASTSCENE};

#define NUM_SCENES _LASTSCENE

class SceneDirector
{
	public:
		~SceneDirector();

		void init();
		
		void changeScene(SceneEnum next_scene, bool reinit = true);

		void changeLastScene(SceneEnum last_scene, bool reinit = true);

		SceneEnum getCurrSceneEnum(){return mCurrScene;};

		SceneEnum getLastSceneEnum(){return mLastScene;};

		Scene* getCurrentScene(){return mVectorScenes[mCurrScene];};
		
		CHARACTERS getSelectedCharacter() { return pCharacter; };

		void setSelectedCharacter(CHARACTERS nCharacter) { pCharacter = nCharacter; };

		//! Gets pointer to instance
		static SceneDirector* getInstance();

	protected:
		SceneDirector();
		static SceneDirector*	pInstance;	/*!<  pointer instance*/

		std::vector<Scene*>	mVectorScenes;
		SceneEnum		mCurrScene;
		SceneEnum		mLastScene;
		CHARACTERS pCharacter;
};

#endif
