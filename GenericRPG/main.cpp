#include <iostream>

#include "Runtime.h"

/**
 * @brief Program entry.
 * 
 * @details Initializes a game Runtime, and runs the basic gameloop
 * 
 * @param argc 
 * @param args 
 * @return 
*/
int main(int argc, char** args) {
	Runtime* game_runtime = new Runtime();

	//kick off the runtime
	while (game_runtime->RunGameLoop());
	return 0;
}