#pragma once
#include <SDL.h>

class KeyEventHandler {
	public:
		virtual void HandleEvent(SDL_KeyboardEvent) = 0;
};


class MouseButtonEventHandler {
public:
	virtual void HandleEvent(SDL_MouseButtonEvent) = 0;
};

class MouseMotionEventHandler {
public:
	virtual void HandleEvent(SDL_MouseMotionEvent) = 0;
};