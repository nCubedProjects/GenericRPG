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
		std::list<MouseMotionEventHandler*> mouseMotionEventHandlers;

		void HandleKeyEvent(SDL_KeyboardEvent);
		void HandleMouseButtonEvent(SDL_MouseButtonEvent);
		void HandleMouseMotionEvent(SDL_MouseMotionEvent);
};

