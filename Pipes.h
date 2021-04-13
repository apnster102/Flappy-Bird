#ifndef __PIPES_
#define __PIPES_

#include "Object.h"
#include <stdlib.h>
#include <ctime>

class Pipe : public Object
{
public:
    Pipe();
    bool loadImage(string path, SDL_Renderer* ren);
    void render(SDL_Renderer* ren, int pos);
    void setPos(int ypos);
    int getPos(){return pos;}
    ~Pipe();
private:
    int pos;

};

class PipePair : public Object
{
public:
    PipePair();
    bool spawnPipes(SDL_Renderer* ren);
    bool collided(SDL_Rect player);
    bool passed(SDL_Rect player);
    void render(SDL_Renderer* ren);
    void roll(SDL_Renderer* ren);
    void setPosX(int pX){posX = pX;}
    void setOffset(int os){offset = os;}
    int getPos(){return posX;}
    ~PipePair();
private:
    Pipe upperPipe, lowerPipe;
    int posX;
    int offset;
};



#endif


