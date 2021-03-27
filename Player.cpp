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
    if(getLiveState())
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

void Player::handleEvent(SDL_Event event, SDL_Renderer* ren)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        step = -5;
        degree = -30;
        flyUp = true;
    }
    else if(event.type == SDL_MOUSEBUTTONUP)
    {
        step = 5;
        degree = 30;
        flyUp = false;
    }
    if(getLiveState())
    {
        step = 0;
        degree = 0;
    }
}

bool Player::getLiveState()
{
    if(rect.y >= 420 || rect.y <= 0)
    {
        isDead = true;
    }
    else isDead = false;
    return isDead;
}
