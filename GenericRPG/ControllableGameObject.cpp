#include "ControllableGameObject.h"

ControllableGameObject::ControllableGameObject() : GameObject() {
	isMoving = false;
}

ControllableGameObject::ControllableGameObject(SDL_Texture* texture) : GameObject(texture) {
	isMoving = false;
}

void ControllableGameObject::HandleEvent(SDL_KeyboardEvent e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.keysym.sym) {
		case SDLK_a: 
			AKeyPressed();
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.keysym.sym) {
		case SDLK_a:
			AKeyReleased();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}


void ControllableGameObject::Render(SDL_Renderer* renderer) {
	if (isMoving) {
		SetLocation(objLocation.x + 1, objLocation.y + 1);
	}

	SDL_RenderCopy(renderer, objTexture, NULL, &objLocation);
}

void ControllableGameObject::AKeyPressed() {
	isMoving = true;
}

void ControllableGameObject::AKeyReleased() {
	isMoving = false;
}