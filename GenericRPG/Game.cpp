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
	

	//Build the game world
	if (!BuildGameWorld()) {
		Shutdown();
		return false;
	}


	return true;
}

bool Game::Run() {
	//Handle Events
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		default:
			break;
		}
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
	GameObject* tmpObj;
	
	try {
		tmpTxtr = textureManager->GetTexturePtr("stickman");
	}
	catch (std::out_of_range) {
		return false;
	}
	
	
	tmpObj = new GameObject(tmpTxtr);
	tmpObj->SetLocation(100, 100);

	gameObjects.push_front(tmpObj);

	return true;
}