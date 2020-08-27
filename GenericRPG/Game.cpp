#include <iostream>
#include <stdexcept>
#include <SDL.h>

#include "Game.h"
#include "GameProperties.h"


Game::Game() {
	window = NULL;
	renderer = NULL;
}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS)) {
		std::cout << "Failed to initialize SDL" << std::endl;
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

		SDL_Quit();
		return false;
	}

	//Load all game textures
	textureManager = new TextureManager(renderer);
	if (!textureManager->Initialize()) {
		std::cout << "Failed to initialize texture manager" << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		SDL_Quit();
		return false;
	}

	//Initialize the event manager
	eventManager = new EventManager();
	

	//Build the game world
	if (!BuildGameWorld()) {
		Shutdown();
		return false;
	}


	return true;
}

bool Game::Run() {
	if (!eventManager->HandleEvents()) {
		return false;
	}

	//Handle Rendering
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	std::list <GameObject *> ::iterator gameObjectPtr;
	for (gameObjectPtr = gameObjects.begin(); gameObjectPtr != gameObjects.end(); ++gameObjectPtr) {
		(*gameObjectPtr)->Render(renderer);
	}

	SDL_RenderPresent(renderer);

	//End game loop iteration
	return true;
}

bool Game::Shutdown() {
	delete eventManager;

	textureManager->Destroy();
	delete textureManager;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return true;
}

bool Game::BuildGameWorld() {
	//TEMP: Add a game object for testing
	SDL_Texture* tmpTxtr;
	ControllableGameObject* tmpObj;
	
	try {
		tmpTxtr = textureManager->GetTexturePtr("stickman");
	}
	catch (std::out_of_range) {
		return false;
	}
	
	
	tmpObj = new ControllableGameObject(tmpTxtr);
	((GameObject*)tmpObj)->SetLocation(100, 100);

	gameObjects.push_front((GameObject*)tmpObj);
	eventManager->RegisterKeyEventHandler((KeyEventHandler *)tmpObj);

	return true;
}