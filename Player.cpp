#include "Player.h"

Player::Player()
{
    upStep = 7;
    fallStep = 1;
    pos_x = 0;
    pos_y = 0;
    frame_width = 0;
    frame_height = 0;
    frame = 0;
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
    SDL_Rect* currentClip = &spriteClips[frame/2];
    frame++;
    if(frame/2 >= 2)
    {
        frame = 0;
    }
    SDL_Rect renderQuad = {rect.x, rect.y, frame_width, frame_height};
    SDL_RenderCopy(ren, tex, currentClip, &renderQuad);
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

void Player::gravity()
{
    rect.y += fallStep;
    cout << "y - " << fallStep << endl;
}

void Player::handleEvent(SDL_Event event, SDL_Renderer* ren)
{
    if(event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP))
    {
        rect.y -= upStep;
        cout << "x + " << upStep << endl;
    }
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_DOWN)
        {
            rect.y += 10;
        }
    }
}
