#include "Object.h"

Object::Object()
{
	tex = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

Object::~Object()
{
	free();
}

bool Object::loadImage(string path, SDL_Renderer* ren)
{
	SDL_Texture* gtexture = NULL;

	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if(tempSurface == NULL)
        cout << "Failed to load Image " << path << " SDL_Image error: " << IMG_GetError() << endl;
    else
	{
		gtexture = SDL_CreateTextureFromSurface(ren, tempSurface);

		if(gtexture == NULL)
            cout << "Failed to get Texture from " << path << " SDL error: " << SDL_GetError() << endl;
		else
		{
		    // Get image dimensions
			rect.w = tempSurface->w;
			rect.h = tempSurface->h;
		}

		SDL_FreeSurface(tempSurface);
	}

	tex = gtexture;

	return tex != NULL;
}

void Object::render(SDL_Renderer* ren, const SDL_Rect* clip)
{
    SDL_Rect renderQuad = { rect.x, rect.y, rect.w, rect.h };
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(ren, tex, clip, &renderQuad);
}

void Object::setRect (const int& x, const int& y)
{
    rect.x = x;
    rect.y = y;
}
SDL_Texture* Object::getTex() const
{
    return tex;
}
SDL_Rect Object::getRect() const
{
    return rect;
}

void Object::free()
{
	if(tex != NULL)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}
