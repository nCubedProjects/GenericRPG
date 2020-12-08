#pragma once

#include <list>

#include "EventHandlers.h"

class EventManager {
	public:
		EventManager();

		bool HandleEvents();
		void RegisterKeyEventHandler(KeyEventHandler *);
		void RegisterMouseButtonEventHandler(MouseButtonEventHandler*);
		void RegisterMouseMotionEventHandler(MouseMotionEventHandler*);
	private:
		std::list<KeyEventHandler *> key_event_handlers;
		std::list<MouseButtonEventHandler*> mousebutton_event_handlers;
		std::list<MouseMotionEventHandler*> mousemotion_event_handlers;

		void HandleKeyEvent(SDL_KeyboardEvent);
		void HandleMouseButtonEvent(SDL_MouseButtonEvent);
		void HandleMouseMotionEvent(SDL_MouseMotionEvent);
};

