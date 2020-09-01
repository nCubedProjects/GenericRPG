#include "SpriteGameObject.h"

SpriteGameObject::SpriteGameObject() : 
	GameObject(), TileSetGameObject() {
	current_frame = 0;
	frame_rate = 0;
	frames_rendered = 0;
}

SpriteGameObject::SpriteGameObject(SDL_Texture * texture,
									int num_across,
									int num_down,
									int sprite_frame_rate) 
	: GameObject(texture), TileSetGameObject(texture, num_across, num_down) {
	current_frame = 0;
	frame_rate = sprite_frame_rate;
	frames_rendered = 0;
}

void SpriteGameObject::Render(SDL_Renderer* renderer) {

	SDL_RenderCopy(renderer, objTexture, &frames[current_frame], &objLocation);

	frames_rendered = (frames_rendered + 1) % frame_rate;
	if(frames_rendered == 0) current_frame = (current_frame + 1) % total_frames;
}