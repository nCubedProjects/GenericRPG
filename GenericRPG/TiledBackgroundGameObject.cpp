#include "TiledBackgroundGameObject.h"

#include <stdlib.h>

TiledBackgroundGameObject::TiledBackgroundGameObject() :
	GameObject(), ViewAwareGameObject(), TileSetGameObject() {
	frame_id_grid = NULL;
}

TiledBackgroundGameObject::TiledBackgroundGameObject(SDL_Texture* texture,
	int view_width,
	int view_height,
	int num_across,
	int num_down)
: GameObject(texture), ViewAwareGameObject(texture, view_width, view_height), TileSetGameObject(texture, num_across, num_down) {

	//Hard coding the frame_id_grid for development
	int frames_across, frames_down;
	frames_across = view.w / objLocation.w;
	frames_down = view.h / objLocation.h;

	frame_id_grid = (Uint8**)malloc(frames_down * sizeof(Uint8*));

	for (int i = 0; i < frames_down; i++) {
		frame_id_grid[i] = (Uint8*)malloc(frames_across * sizeof(Uint8));
		for (int j = 0; j < frames_across; j++) {
			frame_id_grid[i][j] = rand() % total_frames;
		}
	}
}

void TiledBackgroundGameObject::Render(SDL_Renderer* renderer) {

	int frames_across, frames_down;
	frames_across = view.w / objLocation.w;
	frames_down = view.h / objLocation.h;

	SDL_Rect dst = { 0, 0, objLocation.w, objLocation.h };


	for (int i = 0; i < frames_down; i++) {
		for (int j = 0; j < frames_across; j++) {

			dst.x = objLocation.w * j;
			dst.y = objLocation.h * i;
			SDL_RenderCopy(renderer, objTexture, &frames[frame_id_grid[i][j]], &dst);
		}
	}
	

}