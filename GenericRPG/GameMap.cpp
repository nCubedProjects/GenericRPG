#include "GameMap.h"

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

void GameMap::HandleEvent(SDL_MouseMotionEvent event) {
	return;
}