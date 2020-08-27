#include <SDL.h>
#include "EventManager.h"

EventManager::EventManager() {
	keyEventHandlers = std::list<KeyEventHandler *>();
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
		default:
			break;
		}
	}

	return true;
}


void EventManager::RegisterKeyEventHandler(KeyEventHandler * keyEventHandler) {
	keyEventHandlers.push_back(keyEventHandler);
}

void EventManager::HandleKeyEvent(SDL_KeyboardEvent e) {
	bool returnVal = true;
	
	std::list<KeyEventHandler *> ::iterator keyEventHandlerPtr;
	for (keyEventHandlerPtr = keyEventHandlers.begin(); keyEventHandlerPtr != keyEventHandlers.end(); ++keyEventHandlerPtr) {
		(*keyEventHandlerPtr)->HandleEvent(e);
	}
}
