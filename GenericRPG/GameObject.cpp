#include "GameObject.h"

GameObject::GameObject() {
	obj_texture = NULL;
	obj_location = { 0,0,0,0 };
}

GameObject::GameObject(SDL_Texture * texture) {
	obj_texture = texture;
	obj_location = { 0,0,0,0 };

	SDL_QueryTexture(obj_texture, NULL, NULL, &obj_location.w, &obj_location.h);
}

void GameObject::Render(SDL_Renderer * renderer) {
	SDL_RenderCopy(renderer, obj_texture, NULL, &obj_location);
}

void GameObject::SetLocation(int x, int y) {
	obj_location.x = x;
	obj_location.y = y;
}

void GameObject::SetTexture(SDL_Texture * texture) {
	obj_texture = texture;
}