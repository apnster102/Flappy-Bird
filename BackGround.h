#ifndef BACK__GROUND_H_
#define BACK__GROUND_H_

#include "GameLoop.h"

class TextureManager
{
public:
    TextureManager();
    static SDL_Texture* Texture(const char* filePath, SDL_Renderer* ren);

    ~TextureManager();
};



#endif
