#pragma once

#include <list>
#include <SDL.h>

#include "TextureManager.h"
#include "GameObject.h"

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
		std::list<GameObject*> gameObjects;
};

