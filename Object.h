#ifndef OBJECT__H_
#define OBJECT__H_

#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;
const int GROUND_HEIGHT = 50;
const int PIPE_HEIGHT = 300;
const int PIPE_WIDTH = 80;

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

    virtual bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

    void free();

};



#endif
