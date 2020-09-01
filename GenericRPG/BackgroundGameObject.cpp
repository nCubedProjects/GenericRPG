#include "BackgroundGameObject.h"

#include <algorithm>

BackgroundGameObject::BackgroundGameObject() 
	: GameObject() {
	view = { 0,0,0,0 };
}

BackgroundGameObject::BackgroundGameObject(SDL_Texture* texture, int view_width, int view_height)
	: GameObject(texture) {
	int w, h; //temp variables to hold texture width and height

	//don't set view dimensions to something smaller than the background

	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);
	if (view_width > w || view_height > h) {
		throw;
	}

	view = { 0,0,view_width,view_height};
}

void BackgroundGameObject::UpdateViewOrigin(int x, int y) {
	int w, h; //temp variables to hold texture width and height
	
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);


	//Don't set origin past the point that would stretch the background.
		//So if x and y allow the view's width and height to 
		// cover a section of the texture, use them.
		//otherwise set to the largest value that allows the view's width and 
		// height to reach the appropriate edge of the texture.
	view.x = std::min(x,w-view.w);
	view.y = std::min(y,h-view.h);
}

void BackgroundGameObject::UpdateViewDimensions(int view_width ,int view_height) {
	int w, h; //temp variables to hold texture width and height

	//don't set view dimensions to something smaller than the background
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);
	if (view_width > w || view_height > h) {
		throw;
	}
	
	view.w = view_width;
	view.h = view_height;
}

void BackgroundGameObject::Render(SDL_Renderer* renderer) {
	SDL_Rect dst = { 0,0,view.w, view.h };
	SDL_RenderCopy(renderer, objTexture, &view, &dst);
}