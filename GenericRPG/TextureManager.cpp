#include <stdexcept>

#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer) {
	game_renderer = renderer;
	texture_map = new std::map<const char*, SDL_Texture*>();

	
}

TextureManager::~TextureManager() {
	delete texture_map;
}


bool TextureManager::Initialize() {
	//For now manually add all textures here

	if (!AddTexture("stickman.bmp", "stickman")) {
		return false;
	}

	if (!AddTexture("dummytileset.bmp", "dummytileset")) {
		return false;
	}

	if (!AddTexture("desert_background.bmp", "background")) {
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

	if (!DeleteTexture("background")) {
		return false;
	}

	return true;
}


SDL_Texture* TextureManager::GetTexturePtr(const char* textureName) {
	return texture_map->at(textureName);
}


bool TextureManager::AddTexture(const char * filename, const char * textureName) {
	SDL_Surface* load;
	SDL_Texture* newTexture;
	
	load = SDL_LoadBMP(filename);
	if (!load) {
		return false;
	}
	newTexture = SDL_CreateTextureFromSurface(game_renderer, load);

	texture_map->insert(std::pair<const char*, SDL_Texture*>(textureName, newTexture));

	SDL_FreeSurface(load);

	return true;
}

bool TextureManager::DeleteTexture(const char* textureName) {
	SDL_Texture* toDelete;

	try {
		toDelete = texture_map->at(textureName);
		texture_map->erase(textureName);
	}
	catch (std::out_of_range) {
		return false;
	}

	SDL_DestroyTexture(toDelete);

	return true;
}