#pragma once

#include <list>

#include "GameObject.h"
#include "TileSetGameObject.h"
#include "SpriteGameObject.h"
#include "BackgroundGameObject.h"
#include "TiledBackgroundGameObject.h"

#include "ControllableGameObject.h"
#include "GameMap.h"

class Game{
	public:
		Game();
		~Game();
		bool Run();

	private:
		std::list<GameObject*> game_objects;
		bool BuildGameWorld();
};

