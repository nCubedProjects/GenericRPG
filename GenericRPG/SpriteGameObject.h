#pragma once
#include "GameObject.h"
class SpriteGameObject :
	public GameObject {
public:
	SpriteGameObject();
	SpriteGameObject(SDL_Texture* texture, int, int);

	void Render(SDL_Renderer*);
private:
	SDL_Rect* frames;
	int total_frames;
	int current_frame;
};

