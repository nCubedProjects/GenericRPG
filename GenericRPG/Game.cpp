#include <iostream>
#include <stdexcept>
#include <SDL.h>

#include "Game.h"



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
	//capture current ticks for starting frame rate cap
	int start_ticks = SDL_GetTicks();
	
	//Handle Events
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

	//Delay if needed for capping frame rate
	int frameticks = SDL_GetTicks() - start_ticks;
	if (frameticks < screen_ticks_per_frame) {
		SDL_Delay(screen_ticks_per_frame - frameticks);
	}
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
	
	bool tiled = true; //just a quick switch to keep the other background in place
	//Add a background object
	if (!tiled) {
		BackgroundGameObject* tmpBackground;
		try {
			tmpTxtr = textureManager->GetTexturePtr("background");
		}
		catch (std::out_of_range) {
			return false;
		}

		tmpBackground = new BackgroundGameObject(tmpTxtr, INIT_W, INIT_H);
		tmpBackground->UpdateViewOrigin(0, 0); //hard code testing moving around the background

		gameObjects.push_back(tmpBackground);
	}
	else {
		TiledBackgroundGameObject* tmpBackground;
		try {
			tmpTxtr = textureManager->GetTexturePtr("dummytileset");
		}
		catch (std::out_of_range) {
			return false;
		}

		tmpBackground = new TiledBackgroundGameObject(tmpTxtr, INIT_W, INIT_H, 2, 2);
		tmpBackground->UpdateViewOrigin(100, 100); //hard code testing moving around the background

		gameObjects.push_back(tmpBackground);
	}

	//Code to add a "controllable" gme object
		//this object implements a keyeventhander and mousebutton eventhandler
	ControllableGameObject* tmpObj; 

	try {
		tmpTxtr = textureManager->GetTexturePtr("stickman");
	}
	catch (std::out_of_range) {
		return false;
	}
	
	tmpObj = new ControllableGameObject(tmpTxtr);
	((GameObject*)tmpObj)->SetLocation(100, 100);

	gameObjects.push_back((GameObject*)tmpObj);
	eventManager->RegisterKeyEventHandler((KeyEventHandler *)tmpObj);
	eventManager->RegisterMouseButtonEventHandler((MouseButtonEventHandler*)tmpObj);


	//Code to add a "Sprite" object
		// or a game object that renders frames of its texture
	SpriteGameObject* tmpSpriteObj;

	try {
		tmpTxtr = textureManager->GetTexturePtr("dummytileset");
	}
	catch (std::out_of_range) {
		return false;
	}

	tmpSpriteObj = new SpriteGameObject(tmpTxtr, 2, 2, 10);
	gameObjects.push_back((GameObject*)tmpSpriteObj);

	return true;
}