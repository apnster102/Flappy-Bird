#ifndef BACK__GROUND_H_
#define BACK__GROUND_H_

#include "GameLoop.h"

class BackGround
{
public:
    BackGround();
    static SDL_Texture* Texture(const char* filePath, SDL_Renderer* ren);

    ~BackGround();
};



#endif
