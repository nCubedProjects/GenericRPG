#include <stdexcept>

#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer) {
	gameRenderer = renderer;
	textureMap = new std::map<const char*, SDL_Texture*>();

	
}

TextureManager::~TextureManager() {
	delete textureMap;
}


bool TextureManager::Initialize() {
	//For now manually add all textures here

	if (!AddTexture("stickman.bmp", "stickman")) {
		return false;
	}

	if (!AddTexture("dummytileset.bmp", "dummytileset")) {
		return false;
	}

	return true;
}

bool TextureManager::Destroy() {
	if (!DeleteTexture("stickman")) {
		return false;
	}

	if (!DeleteTexture("dummytileset")) {
		return false;
	}

	return true;
}


SDL_Texture* TextureManager::GetTexturePtr(const char* textureName) {
	return textureMap->at(textureName);
}


bool TextureManager::AddTexture(const char * filename, const char * textureName) {
	SDL_Surface* load;
	SDL_Texture* newTexture;
	
	load = SDL_LoadBMP(filename);
	if (!load) {
		return false;
	}
	newTexture = SDL_CreateTextureFromSurface(gameRenderer, load);

	textureMap->insert(std::pair<const char*, SDL_Texture*>(textureName, newTexture));

	SDL_FreeSurface(load);

	return true;
}

bool TextureManager::DeleteTexture(const char* textureName) {
	SDL_Texture* toDelete;

	try {
		toDelete = textureMap->at(textureName);
		textureMap->erase(textureName);
	}
	catch (std::out_of_range) {
		return false;
	}

	SDL_DestroyTexture(toDelete);

	return true;
}