#include <iostream>
#include "Game.h"
#include "GameProperties.h"

Game::Game() {
	window = NULL;
	renderer = NULL;
}

bool Game::Initialize() {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		std::cout << "Failed to initialize SDL." << std::endl;
		return false;
	}

	//Create the game window
	window = SDL_CreateWindow(GAMENAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		INIT_W,
		INIT_H,
		0);
	if (!window) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//Create the main renderer
	renderer = SDL_CreateRenderer(window,
		-1,
		SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Could create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		return false;
	}

	return true;
}

bool Game::Run() {
	//Handle Events
	SDL_Event e;
	while (!SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
			break;
		default:
			break;
		}
	}

	//Handle Rendering
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	//End game loop iteration
	return true;
}

bool Game::Shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return true;
}