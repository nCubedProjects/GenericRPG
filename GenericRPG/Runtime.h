#pragma once
#include <queue>

#include "Properties.h"
#include "TextureManager.h"
#include "EventManager.h"

#include "Game.h"
#include "GameObject.h"

class Runtime {
	public:
		Runtime();
		~Runtime();

		static Runtime* Get();

		SDL_Renderer* Renderer();
		TextureManager* GetTextureManager();
		EventManager* GetEventManager();

		bool RunGameLoop();

		void AddToRenderQueue(GameObject*);

	private:
		static Runtime* game_runtime;
		
		Game* game;

		SDL_Window* window = nullptr;

		SDL_Renderer* renderer = nullptr;
		TextureManager* texture_manager;
		EventManager* event_manager;

		std::queue<GameObject*> render_queue;


		const int screen_ticks_per_frame = SCREEN_TICKS_PER_FRAME;
};

