#pragma once
#include "GameObject.h"
#include "EventHandlers.h"

class ControllableGameObject : 
	GameObject,
	KeyEventHandler,
	MouseButtonEventHandler {
	
public:
	ControllableGameObject();
	ControllableGameObject(SDL_Texture *);

	void HandleEvent(SDL_KeyboardEvent);
	void HandleEvent(SDL_MouseButtonEvent);


	void Render(SDL_Renderer*);

private:
	void AKeyPressed();
	void AKeyReleased();

	void ButtonPressed(int, int);

	bool is_moving;
};

