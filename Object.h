#ifndef OBJECT__H_
#define OBJECT__H_

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

using namespace std;

class Object
{
public:
    Object();
    ~Object();
    void setRect (const int& x, const int& y)
    {
        rect.x = x;
        rect.y = y;
    }
    SDL_Texture* getTex() const
    {
        return tex;
    }
    SDL_Rect getRect() const
    {
        return rect;
    }
    virtual bool loadImage(string path, SDL_Renderer* ren);
    //Render texture at given position
    void render(SDL_Renderer* ren, const SDL_Rect* clip = NULL);
    void free();

protected:
    //img variable
    SDL_Texture* tex;
    //img's size variable
    SDL_Rect rect;
};



#endif
