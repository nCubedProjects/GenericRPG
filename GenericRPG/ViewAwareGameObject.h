#pragma once
#include "GameObject.h"
class ViewAwareGameObject :
	public GameObject {

public:
	ViewAwareGameObject();
	ViewAwareGameObject(SDL_Texture *, int, int);

	virtual void UpdateViewOrigin(int, int);
	virtual void UpdateViewDimensions(int, int);

	virtual void Render(SDL_Renderer*) = 0;

protected:
	SDL_Rect view;

};

