#ifndef BUTTON__H_
#define BUTTON__H_

#include "Object.h"
#include "Text.h"

class Button : public Object
{
public:
    Button();
    ~Button();
    bool chosen(SDL_Event e);
    void RenderButton(SDL_Renderer* ren, string Fuction, TTF_Font* font);
    void handleButtonEvent(SDL_Event e, Mix_Chunk* click, string &show, string choice);
private:
    Text bText;
};




#endif // BUTTON__H
