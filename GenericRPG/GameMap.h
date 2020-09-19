#pragma once

#include "TiledBackgroundGameObject.h"
#include "EventHandlers.h"

class GameMap :
	public TiledBackgroundGameObject,
	public MouseMotionEventHandler
{
public:
	GameMap();
	GameMap(SDL_Texture*, int, int, int, int);

	void HandleEvent(SDL_MouseMotionEvent);
};