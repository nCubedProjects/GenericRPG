#pragma once
#include <queue>
#include <memory>

#include "Properties.h"
#include "TextureManager.h"
#include "EventManager.h"

#include "Game.h"
#include "GameObject.h"

class Runtime {
	public:
		Runtime();
		~Runtime();

		static std::shared_ptr<Runtime> Get();

		std::shared_ptr<SDL_Renderer> GetRenderer();
		std::shared_ptr<TextureManager> GetTextureManager();
		std::shared_ptr<EventManager> GetEventManager();

		bool RunGameLoop();

		void AddToRenderQueue(GameObject*);

	private:
		static std::shared_ptr<Runtime> game_runtime;
		
		Game* game;

		SDL_Window* window = nullptr;

		std::shared_ptr<SDL_Renderer> renderer;
		
		std::shared_ptr<TextureManager> texture_manager;
		std::shared_ptr<EventManager> event_manager;

		std::queue<GameObject*> render_queue;


		const int screen_ticks_per_frame = SCREEN_TICKS_PER_FRAME;
};

