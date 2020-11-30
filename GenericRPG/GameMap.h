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
	void Render(SDL_Renderer*);

private:
	enum Edge { MID, TOP, BOT, LEFT, RIGHT };
	Edge vertical_edge = MID;
	Edge horizontal_edge = MID;
	int inc_speed = 10;
};