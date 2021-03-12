#include "Player.h"

Player::Player()
{
    upStep = 0;
    pos_x = 0;
    pos_y = 0;
}

Player::~Player()
{

}

bool Player::loadImage(const char* path, SDL_Renderer* ren)
{
    bool load = Object::loadImage(path, ren);
    return load;
}

void Player::render(SDL_Renderer* ren)
{
    SDL_Rect renderQuad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(ren, tex, NULL, &renderQuad);
}

void Player::handleEvent(SDL_Event event, SDL_Renderer* ren)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
            rect.x += 5;
        }
        else if(event.key.keysym.sym == SDLK_LEFT)
        {
            rect.x -= 5;
        }
        else if(event.key.keysym.sym == SDLK_UP)
        {
            rect.y -= 5;
        }
        else if(event.key.keysym.sym == SDLK_DOWN)
        {
            rect.y += 5;
        }
    }
}
