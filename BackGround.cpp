#include "BackGround.h"

BackGround::BackGround()
{
    scrollingOffset = 0;
}

BackGround::~BackGround()
{
    free();
}

bool BackGround::loadImage(const char* path, SDL_Renderer* ren)
{
    bool load = Object::loadImage(path, ren);

    return load;
}

void BackGround::render(SDL_Renderer* ren)
{
    Object::render(ren, NULL);
}

void BackGround::groundScrolling(SDL_Renderer* ren)
{
    scrollingOffset -= 2;

    if (scrollingOffset < -rect.w)
	{
		scrollingOffset = 0;
	}
	rect.x = scrollingOffset;
	render(ren);

	rect.x = scrollingOffset + rect.w - 2;
	render(ren);
}

