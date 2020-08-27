#pragma once

#include <list>

#include "EventHandlers.h"

class EventManager {
	public:
		EventManager();

		bool HandleEvents();
		void RegisterKeyEventHandler(KeyEventHandler *);
		void RegisterMouseButtonEventHandler(MouseButtonEventHandler*);
	private:
		std::list<KeyEventHandler *> keyEventHandlers;
		std::list<MouseButtonEventHandler*> mouseButtonEventHandlers;

		void HandleKeyEvent(SDL_KeyboardEvent);
		void HandleMouseButtonEvent(SDL_MouseButtonEvent);
};

