#include <iostream>

#include "Runtime.h"

int main(int argc, char** args) {
	Runtime* game_runtime = new Runtime();

	//kick off the runtime
	while (game_runtime->RunGameLoop());
	return 0;
}