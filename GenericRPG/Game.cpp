#include <iostream>
#include <stdexcept>
#include <SDL.h>

#include "Game.h"
#include "Runtime.h"


/**
 * @brief Constructs a new Game. 
 * 
 * @details This simply consists of "building" the game world for now.
 * Eventually this is where Game specific systems will also be initialized.
*/
Game::Game() {
	//Build the game world
	if (!BuildGameWorld()) {
		throw;
	}
}

/**
 * @brief The Game's core functionality to be run each game loop iteration
 * 
 * @details The current implementation simply adds all objects in the Game's game_object list to the Runtime's render queue
 * 
 * @return Return's true if the game should continue running. False otherwise. 
*/
bool Game::Run() {
	//Get the Runtime singleton
	std::shared_ptr<Runtime> game_runtime = Runtime::Get();
	
	//Add all game_objects to the Runtime's render queue (uses the C++ foreach) 
	for (auto game_object_ptr : game_objects) {
		game_runtime->AddToRenderQueue(game_object_ptr);
	}
	return true;
}

/**
 * @brief Shuts down the Game
 * 
 * @details Doesn't really do anything right now.
*/
Game::~Game() {
}

/**
 * @brief Builds the game world
 * 
 * @details Right now this is a demo function. In a constant state of change.
 It can be used as an example of how to hook into the various Runtime systems.
 * 
 * @return Returns true if the game world was built successfully. False otherwise 
*/
bool Game::BuildGameWorld() {
	//hook into the runtime system to build the game world
	std::shared_ptr<Runtime> game_runtime = Runtime::Get();
	std::shared_ptr<TextureManager> texture_manager = game_runtime->GetTextureManager();
	std::shared_ptr<EventManager> event_manager = game_runtime->GetEventManager();

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