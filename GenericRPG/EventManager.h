#pragma once

#include <list>

#include "KeyEventHandler.h"

class EventManager {
	public:
		EventManager();

		bool HandleEvents();
		void RegisterKeyEventHandler(KeyEventHandler *);
	private:
		std::list<KeyEventHandler *> keyEventHandlers;


		void HandleKeyEvent(SDL_KeyboardEvent);
};

