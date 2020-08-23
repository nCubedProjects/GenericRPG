#include <iostream>
#include "Game.h"

int main(int argc, char** args) {
	Game* game = new Game();

	if (!game->Initialize()) {
		std::cout << "Failed to initialize the game" << std::endl;
		return 1;
	}
	
	while (game->Run());

	game->Shutdown();
	return 0;
}