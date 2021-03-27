#ifndef BACK__GROUND_H_
#define BACK__GROUND_H_

#include "Object.h"

class BackGround : public Object
{
public:
    BackGround();
    bool loadImage(const char* path, SDL_Renderer* ren);
    void render(SDL_Renderer* ren);
    void groundScrolling(SDL_Renderer* ren);

    ~BackGround();

private:
    int scrollingOffset;
};



#endif
