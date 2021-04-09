#ifndef PLAYER__H_
#define PLAYER__H_

#include "Object.h"
#include "Pipes.h"

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
    void setLiveState(bool lState);
    bool hitTheGround();
    SDL_Rect getFrameRect();
private:
    float step;
    int frame_width, frame_height;
    double degree = 0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    bool flyUp;
    bool isDead;
    bool hit;

    SDL_Rect spriteClips[2];
    int frame;
};



#endif
