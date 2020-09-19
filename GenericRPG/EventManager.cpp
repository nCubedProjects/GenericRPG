#include <SDL.h>
#include "EventManager.h"

EventManager::EventManager() {
	keyEventHandlers = std::list<KeyEventHandler *>();
	mouseButtonEventHandlers = std::list<MouseButtonEventHandler*>();
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
	keyEventHandlers.push_back(keyEventHandler);
}

void EventManager::RegisterMouseButtonEventHandler(MouseButtonEventHandler* mouseButtonEventHandler) {
	mouseButtonEventHandlers.push_back(mouseButtonEventHandler);
}

void EventManager::HandleKeyEvent(SDL_KeyboardEvent e) {
	std::list<KeyEventHandler *> ::iterator keyEventHandlerPtr;
	for (keyEventHandlerPtr = keyEventHandlers.begin(); keyEventHandlerPtr != keyEventHandlers.end(); ++keyEventHandlerPtr) {
		(*keyEventHandlerPtr)->HandleEvent(e);
	}
}

void EventManager::HandleMouseButtonEvent(SDL_MouseButtonEvent e) {
	std::list<MouseButtonEventHandler *> ::iterator mouseButtonEventHandlerPtr;
	for (mouseButtonEventHandlerPtr = mouseButtonEventHandlers.begin(); mouseButtonEventHandlerPtr != mouseButtonEventHandlers.end(); ++mouseButtonEventHandlerPtr) {
		(*mouseButtonEventHandlerPtr)->HandleEvent(e);
	}
}

void EventManager::HandleMouseMotionEvent(SDL_MouseMotionEvent e) {
	std::list<MouseMotionEventHandler*> ::iterator mouseMotionEventHandlerPtr;
	for (mouseMotionEventHandlerPtr = mouseMotionEventHandlers.begin(); mouseMotionEventHandlerPtr != mouseMotionEventHandlers.end(); ++mouseMotionEventHandlerPtr) {
		(*mouseMotionEventHandlerPtr)->HandleEvent(e);
	}
}
