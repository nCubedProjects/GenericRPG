#include "TiledBackgroundGameObject.h"

#include <stdlib.h>

TiledBackgroundGameObject::TiledBackgroundGameObject() :
	GameObject(), ViewAwareGameObject(), TileSetGameObject() {
	frame_id_grid = NULL;
	generatedBackground = NULL;
}

TiledBackgroundGameObject::TiledBackgroundGameObject(SDL_Texture* texture,
	int view_width,
	int view_height,
	int num_across,
	int num_down)
: GameObject(texture), ViewAwareGameObject(texture, view_width, view_height), TileSetGameObject(texture, num_across, num_down) {
	generateBackground();
	generatedBackground = NULL;
}


void TiledBackgroundGameObject::generateBackground() {
	//Hard coding the frame_id_grid for development
	int frames_across, frames_down;
	frames_across = 2 * (view.w / objLocation.w);
	frames_down = 2 * (view.h / objLocation.h);


	frame_id_grid = (Uint8**)malloc(frames_down * sizeof(Uint8*));

	for (int i = 0; i < frames_down; i++) {
		frame_id_grid[i] = (Uint8*)malloc(frames_across * sizeof(Uint8));
		for (int j = 0; j < frames_across; j++) {
			frame_id_grid[i][j] = rand() % total_frames;
		}
	}
}

void TiledBackgroundGameObject::Render(SDL_Renderer* renderer) {
	//TMP CODE
	//First time Render is called, generate map
	if (!generatedBackground) {
		int frames_across, frames_down;
		frames_across = 2 * (view.w / objLocation.w);
		frames_down = 2 * (view.h / objLocation.h);
		
		generatedBackground = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, frames_across * objLocation.w, frames_down * objLocation.h);
		SDL_SetRenderTarget(renderer, generatedBackground);

		SDL_Rect dst = { 0, 0, objLocation.w, objLocation.h };
		for (int i = 0; i < frames_down; i++) {
			for (int j = 0; j < frames_across; j++) {

				dst.x = objLocation.w * j;
				dst.y = objLocation.h * i;
				SDL_RenderCopy(renderer, objTexture, &frames[frame_id_grid[i][j]], &dst);
			}
		}

		SDL_SetRenderTarget(renderer, NULL);
	}

	
	SDL_Rect dst = { 0,0,view.w, view.h };
	SDL_RenderCopy(renderer, generatedBackground, &view, &dst);
}