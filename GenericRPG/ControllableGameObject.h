#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"

class ControllableGameObject : 
	GameObject,
	KeyEventHandler {
	
public:
	ControllableGameObject();
	ControllableGameObject(SDL_Texture *);

	void HandleEvent(SDL_KeyboardEvent);

	void Render(SDL_Renderer*);

private:
	void AKeyPressed();

	void AKeyReleased();

	bool isMoving;
};

