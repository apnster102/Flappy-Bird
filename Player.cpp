#include "Player.h"

Player::Player()
{
    step = 0;
    frame_width = 0;
    frame_height = 0;
    frame = 0;

    isDead = false;
    flyUp = false;
}

Player::~Player()
{
    free();
}

bool Player::loadImage(const char* path, SDL_Renderer* ren)
{
    bool load = Object::loadImage(path, ren);

    if(load)
    {
        frame_width = rect.w/2;
        frame_height = rect.h;
    }

    return load;
}

void Player::render(SDL_Renderer* ren)
{
    if(isDead)
        loadImage("image/dieGreen.png", ren);
    else
        loadImage("image/flyGreen.png", ren);

    SDL_Rect* currentClip = &spriteClips[frame/2];

    if(flyUp)
        frame++;
    else
        frame = 2;
    if(frame/2 >= 2)
    {
        frame = 0;
    }
    SDL_Rect renderQuad = {rect.x, rect.y, frame_width, frame_height};
    SDL_RenderCopyEx(ren, tex, currentClip, &renderQuad, degree, NULL, flipType);
}

void Player::setSprite()
{
    spriteClips[0].x = 0;
    spriteClips[0].y = 0;
    spriteClips[0].w = frame_width;
    spriteClips[0].h = frame_height;

    spriteClips[1].x = frame_width;
    spriteClips[1].y = 0;
    spriteClips[1].w = frame_width;
    spriteClips[1].h = frame_height;
}

void Player::move()
{
    rect.y += step;
}

void Player::handleEvent(SDL_Event event)
{
    if(flyUp)
    {
        step = -5;
        degree = -30;
    }
    else
    {
        step = 5;
        degree = 30;
    }

    if(event.type == SDL_KEYDOWN && !getLiveState())
    {
        if(event.key.keysym.sym == SDLK_SPACE)
            flyUp = true;
    }
    else if(event.type == SDL_KEYUP||getLiveState())
    {
        flyUp = false;
    }
    //if the bird hit the ground
    if(rect.y >= SCREEN_HEIGHT-rect.h-GROUND_HEIGHT || rect.y <= 0)
    {
        step = 0;
        degree = 0;
    }
}

bool Player::getLiveState()
{
    return isDead;
}

void Player::setLiveState(bool lState)
{
    isDead = lState;
}

SDL_Rect Player::getFrameRect()
{
    SDL_Rect pRect;

    pRect.x = rect.x;
    pRect.y = rect.y;
    pRect.w = rect.w/2;
    pRect.h = rect.h;

    return pRect;
}
