#pragma once
#include "TileSetGameObject.h"
#include "ViewAwareGameObject.h"

class TiledBackgroundGameObject:
	public ViewAwareGameObject,
	public	TileSetGameObject
{
public:
	TiledBackgroundGameObject();
	TiledBackgroundGameObject(SDL_Texture*, int, int, int, int);

	virtual void Render(SDL_Renderer *);

protected:
	Uint8** frame_id_grid;
	SDL_Texture* generated_background;

	void GenerateBackground();
};

