#pragma once
#include <SDL.h>

class KeyEventHandler {
	public:
		virtual void HandleEvent(SDL_KeyboardEvent) = 0;
};

