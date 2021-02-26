#include "TextureManager.h"

SDL_Texture* TextureManager::Texture(const char* filePath, SDL_Renderer* ren)
{
    SDL_Texture* gtexture;
    SDL_Surface* tempSurface;
    tempSurface = IMG_Load(filePath);
    gtexture = SDL_CreateTextureFromSurface(ren, tempSurface);
    return gtexture;
}
