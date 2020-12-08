#include <SDL.h>
#include "EventManager.h"

EventManager::EventManager() {
	key_event_handlers = std::list<KeyEventHandler *>();
	mousebutton_event_handlers = std::list<MouseButtonEventHandler*>();
}

bool EventManager::HandleEvents() {
	//Handle SDL Events
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			HandleKeyEvent(e.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			HandleMouseButtonEvent(e.button);
			break;
		case SDL_MOUSEMOTION:
			HandleMouseMotionEvent(e.motion);
		default:
			break;
		}
	}

	return true;
}


void EventManager::RegisterKeyEventHandler(KeyEventHandler * keyEventHandler) {
	key_event_handlers.push_back(keyEventHandler);
}

void EventManager::RegisterMouseButtonEventHandler(MouseButtonEventHandler* mouseButtonEventHandler) {
	mousebutton_event_handlers.push_back(mouseButtonEventHandler);
}

void EventManager::RegisterMouseMotionEventHandler(MouseMotionEventHandler* mouseMotionEventHandler) {
	mousemotion_event_handlers.push_back(mouseMotionEventHandler);
}

void EventManager::HandleKeyEvent(SDL_KeyboardEvent e) {
	std::list<KeyEventHandler *> ::iterator keyEventHandlerPtr;
	for (keyEventHandlerPtr = key_event_handlers.begin(); keyEventHandlerPtr != key_event_handlers.end(); ++keyEventHandlerPtr) {
		(*keyEventHandlerPtr)->HandleEvent(e);
	}
}

void EventManager::HandleMouseButtonEvent(SDL_MouseButtonEvent e) {
	std::list<MouseButtonEventHandler *> ::iterator mouseButtonEventHandlerPtr;
	for (mouseButtonEventHandlerPtr = mousebutton_event_handlers.begin(); mouseButtonEventHandlerPtr != mousebutton_event_handlers.end(); ++mouseButtonEventHandlerPtr) {
		(*mouseButtonEventHandlerPtr)->HandleEvent(e);
	}
}

void EventManager::HandleMouseMotionEvent(SDL_MouseMotionEvent e) {
	std::list<MouseMotionEventHandler*> ::iterator mouseMotionEventHandlerPtr;
	for (mouseMotionEventHandlerPtr = mousemotion_event_handlers.begin(); mouseMotionEventHandlerPtr != mousemotion_event_handlers.end(); ++mouseMotionEventHandlerPtr) {
		(*mouseMotionEventHandlerPtr)->HandleEvent(e);
	}
}
