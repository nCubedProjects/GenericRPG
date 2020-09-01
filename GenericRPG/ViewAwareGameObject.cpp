#include "ViewAwareGameObject.h"

ViewAwareGameObject::ViewAwareGameObject()
	: GameObject() {
	view = { 0,0,0,0 };
}

ViewAwareGameObject::ViewAwareGameObject(SDL_Texture* texture,
	int view_width,
	int view_height)
	: GameObject(texture) {

	view = { 0,0,view_width,view_height };
}

void ViewAwareGameObject::UpdateViewOrigin(int x, int y) {
	view.x = x;
	view.y = y;
}

void ViewAwareGameObject::UpdateViewDimensions(int view_width, int view_height) {
	view.w = view_width;
	view.h = view_height;
}