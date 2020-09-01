#include "BackgroundGameObject.h"

BackgroundGameObject::BackgroundGameObject() 
	: GameObject() {
	view = { 0,0,0,0 };
}

BackgroundGameObject::BackgroundGameObject(SDL_Texture* texture)
	: GameObject(texture) {
	view = { 0,0,0,0 };
}

void BackgroundGameObject::UpdateViewOrigin(int x, int y) {
	view.x = x;
	view.y = y;
}

void BackgroundGameObject::UpdateViewDimensions(int w, int h) {
	view.w = w;
	view.h = h;
}

void BackgroundGameObject::Render(SDL_Renderer* renderer) {
	SDL_Rect dst = { 0,0,view.w, view.h };
	SDL_RenderCopy(renderer, objTexture, &view, &dst);
}