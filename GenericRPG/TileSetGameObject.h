#pragma once
#include "GameObject.h"
class TileSetGameObject :
	public GameObject {
public:
	TileSetGameObject();
	TileSetGameObject(SDL_Texture* texture, int, int);

	virtual void Render(SDL_Renderer*);
private:
	SDL_Rect* frames;
	int total_frames;
	int current_frame;
};

