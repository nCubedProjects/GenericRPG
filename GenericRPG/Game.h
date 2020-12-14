#pragma once

#include <list>

#include "GameObject.h"
#include "TileSetGameObject.h"
#include "SpriteGameObject.h"
#include "BackgroundGameObject.h"
#include "TiledBackgroundGameObject.h"

#include "ControllableGameObject.h"
#include "GameMap.h"

/**
 * @brief The basic Game object containing game specific logic
 * 
 * @details The Game class will the the Game from the user's experience more or less
 * It will utilize the Runtime for any generic systems required
*/
class Game{
	public:
		Game();
		~Game();
		bool Run();

	private:
		std::list<GameObject*> game_objects;
		bool BuildGameWorld();
};

