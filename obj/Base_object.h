#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "SDL_utils.h"
#include <SDL_image.h>

class Base_object
{
public:
    Base_object();
    ~Base_object();
    void set_rect (const int& x, const int& y)
    {
        rect.x = x;
        rect.y = y;
    }
    SDL_Texture* get_object() const
    {
        return object;
    }
    SDL_Rect get_rect() const
    {
        return rect;
    }
    bool load_Image(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void free();

protected:
    //img variable
    SDL_Texture* object;
    //img size
    SDL_Rect rect;
};



#endif
