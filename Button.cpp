#include "Button.h"

Button::Button()
{

}

Button::~Button()
{
    free();
}

bool Button::chosen(SDL_Event e)
{
    int mX, mY;
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        SDL_GetMouseState(&mX, &mY);

        if(mX >= rect.x && mX <= rect.x + rect.w && mY >= rect.y && mY <= rect.y + rect.h)
        {
            return true;
        }
        else return false;
    }
}

void Button::RenderButton(SDL_Renderer* ren, string Fuction, TTF_Font* font)
{
    render(ren, NULL);
    bText.SetText(Fuction);
    bText.loadFromRenderedText(font, ren);
    bText.RenderText(ren, rect.x+rect.w/2 - bText.getWidth()/2, rect.y+rect.h/2 - bText.getHeight()/2 - 2);
}

void Button::handleButtonEvent(SDL_Event e, Mix_Chunk* click, string &show, string choice)
{
    if(chosen(e))
    {
        bText.setColor(0, 0, 0, 0);
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(show != choice)
                Mix_PlayChannel(-1, click, 0);
            show = choice;
            cout << show << endl;
        }
    }
    else
        bText.setColor(255, 255, 255, 255);
}
