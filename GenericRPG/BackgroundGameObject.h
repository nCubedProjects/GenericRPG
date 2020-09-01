#pragma once
#include "ViewAwareGameObject.h"

class BackgroundGameObject :
	public ViewAwareGameObject {

	public:
		BackgroundGameObject();
		BackgroundGameObject(SDL_Texture*, int, int);

		void UpdateViewOrigin(int, int);
		void UpdateViewDimensions(int, int);

		void Render(SDL_Renderer *);
};

