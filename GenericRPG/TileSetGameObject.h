#pragma once
#include "GameObject.h"
class TileSetGameObject :
	public virtual GameObject {
public:
	TileSetGameObject();
	TileSetGameObject(SDL_Texture* texture, int, int);

	virtual void Render(SDL_Renderer*);
protected:
	SDL_Rect* frames;
	int total_frames;
};

