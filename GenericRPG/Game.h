#pragma once

#include <list>
#include <SDL.h>

#include "TextureManager.h"
#include "EventManager.h"
#include "GameObject.h"
#include "ControllableGameObject.h"
#include "SpriteGameObject.h"

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
};

