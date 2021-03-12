#include "Base_object.h"

Base_object::Base_object()
{
	object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

Base_object::~Base_object()
{
	free();
}

bool Base_object::load_Image(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if(load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 0, 204, 204));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if(new_texture != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	object = new_texture;

	return object != NULL;
}

void Base_object::render(SDL_Renderer* des, const SDL_Rect*clip/*=NULL*/)
{
	SDL_Rect renderstuff = {rect.x, rect.y, rect.w, rect.h};

	SDL_RenderCopy(des, object, clip, &renderstuff);
}

void Base_object::free()
{
	if(object != NULL)
	{
		SDL_DestroyTexture(object);
		object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}
