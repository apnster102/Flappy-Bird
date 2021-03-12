#include "BackGround.h"

SDL_Texture* TextureManager::Texture(const char* filePath, SDL_Renderer* ren)
{
    SDL_Texture* gtexture;
    SDL_Surface* tempSurface;
    tempSurface = IMG_Load(filePath);
    gtexture = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 255, 255, 255));
    SDL_FreeSurface(tempSurface);
    return gtexture;
}
