#include <iostream>

#include "Runtime.h"

std::shared_ptr<Runtime> Runtime::game_runtime;

Runtime::Runtime()
{
	//set the singleton pointer
	game_runtime = std::shared_ptr<Runtime>(this);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		std::cout << "Failed to initialize SDL" << std::endl;
		throw;
	}

	//Create the game window
	// using shared_ptr, so pass in the Destroy function as the Deleter
	window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(GAMENAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		INIT_W,
		INIT_H,
		0), SDL_DestroyWindow);
	if (!window) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		throw;
	}

	//Create the main renderer
	// using shared_ptr, so pass in the Destroy function as the Deleter
	renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window.get(),
		-1,
		SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
	if (!renderer) {
		std::cout << "Could create renderer: " << SDL_GetError() << std::endl;
		SDL_Quit();
		throw;
	}

	//Load all game textures
	texture_manager = std::shared_ptr<TextureManager>(new TextureManager());
	if (!texture_manager->Initialize()) {
		std::cout << "Failed to initialize texture manager" << std::endl;
		SDL_Quit();
		throw;
	}

	//Initialize the event manager
	event_manager = std::shared_ptr<EventManager>(new EventManager());

	//initialize the game
	game = std::shared_ptr<Game>(new Game());
}

Runtime::~Runtime() {
	texture_manager->Destroy();
	SDL_Quit();
}

std::shared_ptr<Runtime> Runtime::Get() {
	if(game_runtime)
		return game_runtime;
	
	throw;
	return nullptr;
}

std::shared_ptr<SDL_Renderer> Runtime::GetRenderer() {
	return renderer;
}

std::shared_ptr<TextureManager> Runtime::GetTextureManager() {
	return texture_manager;
}

std::shared_ptr<EventManager> Runtime::GetEventManager() {
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
	SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
	SDL_RenderClear(renderer.get());

	while(!render_queue.empty()){
		GameObject* game_object_ptr = render_queue.front();
		render_queue.pop();
		//TODO: make the various objects take a shared_ptr
		game_object_ptr->Render(renderer.get());
	}
	SDL_RenderPresent(renderer.get());


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
