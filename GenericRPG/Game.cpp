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
	for (auto game_object_ptr : game_objects) {
		game_runtime->AddToRenderQueue(game_object_ptr);
	}
	return true;
}

Game::~Game() {
}


bool Game::BuildGameWorld() {
	//hook into the runtime system to build the game world
	Runtime* game_runtime = Runtime::Get();
	TextureManager* texture_manager = game_runtime->GetTextureManager();
	EventManager* event_manager = game_runtime->GetEventManager();

	//TEMP: Add a game object for testing
	SDL_Texture* tmpTxtr;
	
	
	GameMap* tmpBackground;
	try {
		tmpTxtr = texture_manager->GetTexturePtr("dummytileset");
	}
	catch (std::out_of_range) {
		return false;
	}

	tmpBackground = new GameMap(tmpTxtr, INIT_W, INIT_H, 2, 2);
	tmpBackground->UpdateViewOrigin(100, 100); //hard code testing moving around the background

	game_objects.push_back(tmpBackground);
	event_manager->RegisterMouseMotionEventHandler((MouseMotionEventHandler*)tmpBackground);

	//Code to add a "controllable" gme object
		//this object implements a keyeventhander and mousebutton eventhandler
	ControllableGameObject* tmpObj; 

	try {
		tmpTxtr = texture_manager->GetTexturePtr("stickman");
	}
	catch (std::out_of_range) {
		return false;
	}
	
	tmpObj = new ControllableGameObject(tmpTxtr);
	((GameObject*)tmpObj)->SetLocation(100, 100);

	game_objects.push_back((GameObject*)tmpObj);
	event_manager->RegisterKeyEventHandler((KeyEventHandler *)tmpObj);
	event_manager->RegisterMouseButtonEventHandler((MouseButtonEventHandler*)tmpObj);


	//Code to add a "Sprite" object
		// or a game object that renders frames of its texture
	SpriteGameObject* tmpSpriteObj;

	try {
		tmpTxtr = texture_manager->GetTexturePtr("dummytileset");
	}
	catch (std::out_of_range) {
		return false;
	}

	tmpSpriteObj = new SpriteGameObject(tmpTxtr, 2, 2, 10);
	game_objects.push_back((GameObject*)tmpSpriteObj);

	return true;
}