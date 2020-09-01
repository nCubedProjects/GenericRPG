#pragma once

#include <list>
#include <SDL.h>

#include "GameProperties.h"

#include "TextureManager.h"
#include "EventManager.h"
#include "GameObject.h"
#include "ControllableGameObject.h"
#include "TileSetGameObject.h"
#include "SpriteGameObject.h"
#include "BackgroundGameObject.h"
#include "TiledBackgroundGameObject.h"

class Game{
	public:
		Game();
		bool Initialize();
		bool Run();
		bool Shutdown();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		TextureManager* textureManager;
		EventManager* eventManager;
		std::list<GameObject*> gameObjects;

		bool BuildGameWorld();

		const int screen_ticks_per_frame = SCREEN_TICKS_PER_FRAME;
};

