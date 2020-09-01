#pragma once
#include "TileSetGameObject.h"
class SpriteGameObject :
	public TileSetGameObject {

public:
	SpriteGameObject();
	SpriteGameObject(SDL_Texture*, int, int, int);

	void Render(SDL_Renderer *);

private:
	int current_frame; //index for the current frame to be rendered
	int frame_rate; //"frames per frame", so how many screen frames each sprite frame is rendered for
	int frames_rendered; //how many screen frames the current sprite frame hasa been rendered
};

