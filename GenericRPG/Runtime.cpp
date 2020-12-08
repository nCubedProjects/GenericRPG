#include <iostream>

#include "Runtime.h"

std::shared_ptr<Runtime> Runtime::game_runtime;

Runtime::Runtime()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		std::cout << "Failed to initialize SDL" << std::endl;
		throw;
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
		throw;
	}

	//Create the main renderer
	renderer = SDL_CreateRenderer(window,
		-1,
		SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Could create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);

		SDL_Quit();
		throw;
	}

	//Load all game textures
	texture_manager = new TextureManager(renderer);
	if (!texture_manager->Initialize()) {
		std::cout << "Failed to initialize texture manager" << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		SDL_Quit();
		throw;
	}

	//Initialize the event manager
	event_manager = new EventManager();

	//set the singleton pointer
	game_runtime = std::shared_ptr<Runtime>(this);

	//initialize the game
	game = new Game();
}

Runtime::~Runtime() {
	delete event_manager;

	texture_manager->Destroy();
	delete texture_manager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

std::shared_ptr<Runtime> Runtime::Get() {
	if(game_runtime)
		return game_runtime;
	
	throw;
	return nullptr;
}

SDL_Renderer* Runtime::Renderer() {
	return renderer;
}

TextureManager* Runtime::GetTextureManager() {
	return texture_manager;
}

EventManager* Runtime::GetEventManager() {
	return event_manager;
}

bool Runtime::RunGameLoop() {
	//capture current ticks for starting frame rate cap
	int start_ticks = SDL_GetTicks();

	//Handle Events
	if (!event_manager->HandleEvents()) {
		return false;
	}

	//run a game specific frame
	if (!game->Run()) {
		return false;
	}

	//Handle Rendering
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	while(!render_queue.empty()){
		GameObject* game_object_ptr = render_queue.front();
		render_queue.pop();
		game_object_ptr->Render(renderer);
	}
	SDL_RenderPresent(renderer);


	//Delay if needed for capping frame rate
	int frameticks = SDL_GetTicks() - start_ticks;
	if (frameticks < screen_ticks_per_frame) {
		SDL_Delay(screen_ticks_per_frame - frameticks);
	}
	//End game loop iteration
	return true;
}

void Runtime::AddToRenderQueue(GameObject* game_object_ptr){
	render_queue.push(game_object_ptr);
}