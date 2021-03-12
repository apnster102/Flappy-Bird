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
        cout << "Failed to load Image!" << endl;
    else
	{
		//SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 255, 255, 255));
		gtexture = SDL_CreateTextureFromSurface(ren, tempSurface);

		if(gtexture == NULL)
            cout << "Failed to get Texture!" << endl;
		else
		{
		    // Get image dimensions
			rect.w = (tempSurface->w)/2;
			rect.h = (tempSurface->h)/2;
		}

		SDL_FreeSurface(tempSurface);
	}

	tex = gtexture;

	return tex != NULL;
}

void Object::render(SDL_Renderer* ren, const SDL_Rect* clip)
{
    //Set rendering space and render to screen
	SDL_Rect renderQuad = {rect.x, rect.y, rect.w, rect.h};

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

	SDL_RenderCopy(ren, tex, clip, &renderQuad);
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
