#include "GameObject.h"

GameObject::GameObject() {
	objTexture = NULL;
	objLocation = { 0,0,0,0 };
}

GameObject::GameObject(SDL_Texture * texture) {
	objTexture = texture;
	objLocation = { 0,0,0,0 };

	SDL_QueryTexture(objTexture, NULL, NULL, &objLocation.w, &objLocation.h);
}

void GameObject::Render(SDL_Renderer * renderer) {
	SDL_RenderCopy(renderer, objTexture, NULL, &objLocation);
}

void GameObject::SetLocation(int x, int y) {
	objLocation.x = x;
	objLocation.y = y;
}

void GameObject::SetTexture(SDL_Texture * texture) {
	objTexture = texture;
}