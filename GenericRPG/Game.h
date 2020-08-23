#pragma once
#include <SDL.h>

class Game{
	public:
		Game();
		bool Initialize();
		bool Run();
		bool Shutdown();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};

