#pragma once
#include "GameObject.h"

class BackgroundGameObject :
	public GameObject {

	public:
		BackgroundGameObject();
		BackgroundGameObject(SDL_Texture*);

		void UpdateViewOrigin(int, int);
		void UpdateViewDimensions(int, int);

		void Render(SDL_Renderer *);

	protected:
		SDL_Rect view;
};

