#ifndef PLAYER__H_
#define PLAYER__H_

#include "Object.h"

class Player : public Object
{
public:
    Player();
    ~Player();

    bool loadImage(const char* path, SDL_Renderer* ren);
    void render(SDL_Renderer* ren);
    void handleEvent(SDL_Event event, SDL_Renderer* ren);

private:
    float upStep;
    float pos_x, pos_y;
};



#endif
