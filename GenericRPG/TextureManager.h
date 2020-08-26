#pragma once

#include <map>

#include <SDL.h>

class TextureManager {
    public: 
        TextureManager(SDL_Renderer *);
        ~TextureManager();

        bool Initialize();
        bool Destroy();

        SDL_Texture *GetTexturePtr(const char *);


    private:
        bool AddTexture(const char *, const char *);
        bool DeleteTexture(const char*);

        std::map<const char *, SDL_Texture *> *textureMap;
        SDL_Renderer* gameRenderer;
};

