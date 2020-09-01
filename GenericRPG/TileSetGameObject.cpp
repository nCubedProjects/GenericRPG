#include "TileSetGameObject.h"

TileSetGameObject::TileSetGameObject() : GameObject() {
	frames = NULL;
	total_frames = 0;
}

TileSetGameObject::TileSetGameObject(SDL_Texture * texture, 
									int num_across,			//the number of frames across the texture (left to right)
									int num_down)			//the number of frames down the texture (top to bottom)
	: GameObject(texture) {

	
	int w, h;	//temp vars for a single frame's width and height in pixels.
	SDL_QueryTexture(objTexture, NULL, NULL, &w, &h);

	//calculate the size of one frame
	w = w / num_across;
	h = h / num_down;

	//set the default location width and height to be the size of one frame, not the whole texture
	objLocation.w = w;
	objLocation.h = h;


	//initialize the frames
		//each frame will have the same size
		//but the origin will point to the top left corner of each frame
	total_frames = num_across * num_down;
	frames = (SDL_Rect*)malloc(total_frames * sizeof(SDL_Rect));
	
	for (int i = 0; i < num_down; i++) {
		for (int j = 0; j < num_across; j++) {
			int frame_index = (i * num_across) + j;
			frames[frame_index].x = j * w;
			frames[frame_index].y = i * h;
			frames[frame_index].w = w;
			frames[frame_index].h = h;
		}
	}

	
}

void TileSetGameObject::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, objTexture, &frames[0], &objLocation);
}