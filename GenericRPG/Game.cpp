#include <iostream>
#include <stdexcept>
#include <SDL.h>

#include "Game.h"
#include "Runtime.h"



Game::Game() {
	//Build the game world
	if (!BuildGameWorld()) {
		throw;
	}
}

bool Game::Run() {
	//this sets up for allowing a different set of objects to be renderer each frame.
	Runtime* game_runtime = Runtime::Get();
	for (auto game_object_ptr : gameObjects) {
		game_runtime->AddToRenderQueue(game_object_ptr);
	}
	return true;
}

Game::~Game() {
}


bool Game::BuildGameWorld() {
	//hook into the runtime system to build the game world
	Runtime* game_runtime = Runtime::Get();
	TextureManager* textureManager = game_runtime->GetTextureManager();
	EventManager* eventManager = game_runtime->GetEventManager();

	//TEMP: Add a game object for testing
	SDL_Texture* tmpTxtr;
	
	
	GameMap* tmpBackground;
	try {
		tmpTxtr = textureManager->GetTexturePtr("dummytileset");
	}
	catch (std::out_of_range) {
		return false;
	}

	tmpBackground = new GameMap(tmpTxtr, INIT_W, INIT_H, 2, 2);
	tmpBackground->UpdateViewOrigin(100, 100); //hard code testing moving around the background

	gameObjects.push_back(tmpBackground);
	eventManager->RegisterMouseMotionEventHandler((MouseMotionEventHandler*)tmpBackground);

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