#include "BackGround.h"

SDL_Texture* BackGround::Texture(const char* filePath, SDL_Renderer* ren)
{
    SDL_Texture* gtexture;
    SDL_Surface* tempSurface;
    tempSurface = IMG_Load(filePath);
    gtexture = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    return gtexture;
}
