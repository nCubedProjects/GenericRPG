#include "GameMap.h"

#include <iostream>

GameMap::GameMap() :
	GameObject(),
	TiledBackgroundGameObject() {
}


GameMap::GameMap(SDL_Texture* texture,
	int view_width,
	int view_height,
	int num_across,
	int num_down) :
	GameObject(texture),
	TiledBackgroundGameObject(texture,view_width,view_height,num_across,num_down) {
}

void GameMap::HandleEvent(SDL_MouseMotionEvent mouse) {
	if (mouse.x < 50) {
		//left edge
		vertical_edge = LEFT;
	}
	else if (mouse.x > view.w - 50) {
		//right edge
		vertical_edge = RIGHT;
	}
	else {
		//middle
		vertical_edge = MID;
	}

	if (mouse.y < 50) {
		//top edge
		horizontal_edge = TOP;
	}
	else if (mouse.y > view.h - 50) {
		//bottom edge
		horizontal_edge = BOT;
	}
	else {
		//middle
		horizontal_edge = MID;
	}
	return;
}

void GameMap::Render(SDL_Renderer* renderer) {
	switch (vertical_edge) {
	case LEFT:
		if(view.x >= inc_speed) view.x -= inc_speed;
		break;
	case RIGHT:
		if(view.x <= view.w- inc_speed) view.x += inc_speed;
		break;
	default:
		break;
	}

	switch (horizontal_edge) {
	case TOP:
		if(view.y >= inc_speed) view.y -= inc_speed;
		break;
	case BOT:
		if(view.y <= view.h- inc_speed) view.y += inc_speed;
		break;
	default:
		break;
	}

	TiledBackgroundGameObject::Render(renderer);
}