#pragma once
#include <SDL.h>
class GameObject {
	public:
		GameObject();
		GameObject(SDL_Texture *);

		virtual void Render(SDL_Renderer *);
		
		virtual void SetLocation(int, int);
		virtual void SetTexture(SDL_Texture*);
	
	protected:
		SDL_Texture *	obj_texture;
		SDL_Rect		obj_location;
};

