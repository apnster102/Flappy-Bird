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
    void setSprite();
    void gravity();

private:
    float upStep, fallStep;
    float pos_x, pos_y;
    int frame_width, frame_height;

    SDL_Rect spriteClips[2];
    int frame;
};



#endif
