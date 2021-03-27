#ifndef OBJECT__H_
#define OBJECT__H_

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>

using namespace std;

class Object
{
protected:
    //img variable
    SDL_Texture* tex;
    //img's size variable
    SDL_Rect rect;

public:
    Object();
    ~Object();
    virtual void setRect (const int& x, const int& y);

    SDL_Texture* getTex() const;

    SDL_Rect getRect() const;

    virtual bool loadImage(string path, SDL_Renderer* ren);

    void render(SDL_Renderer* ren, const SDL_Rect* clip);

    void free();

};



#endif
