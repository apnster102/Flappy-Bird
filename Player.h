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
    void move();
    bool getLiveState();
private:
    float step;
    int frame_width, frame_height;
    double degree = 0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    bool flyUp;
    bool isDead;

    SDL_Rect spriteClips[2];
    int frame;
};



#endif
