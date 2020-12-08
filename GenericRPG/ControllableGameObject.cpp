#include "ControllableGameObject.h"

ControllableGameObject::ControllableGameObject() : GameObject() {
	is_moving = false;
}

ControllableGameObject::ControllableGameObject(SDL_Texture* texture) : GameObject(texture) {
	is_moving = false;
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

void ControllableGameObject::HandleEvent(SDL_MouseButtonEvent e) {
	switch (e.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button) {
		case SDL_BUTTON_LEFT:
			ButtonPressed(e.x, e.y);
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
	if (is_moving) {
		SetLocation(obj_location.x + 1, obj_location.y + 1);
	}

	SDL_RenderCopy(renderer, obj_texture, NULL, &obj_location);
}

void ControllableGameObject::AKeyPressed() {
	is_moving = true;
}

void ControllableGameObject::AKeyReleased() {
	is_moving = false;
}

void ControllableGameObject::ButtonPressed(int x, int y) {
	SetLocation(x, y);
}