#include "Text.h"

Text::Text(void)
{
  text_color.r = 255;
  text_color.g = 255;
  text_color.b = 255;
  text_color.a = 255;
}


Text::~Text(void)
{
    Free();
}


bool Text::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* ren)
{
  SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, content.c_str(), text_color);
  if( textSurface != NULL )
  {
    texture = SDL_CreateTextureFromSurface(ren, textSurface );
    if( texture != NULL )
    {
      text_width = textSurface->w;
      text_height = textSurface->h;
    }

    SDL_FreeSurface( textSurface );
  }

  return texture != NULL;
}

void Text::Free()
{
  if(texture != NULL)
  {
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
}

void Text::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  text_color.r = red;
  text_color.g = green;
  text_color.b = blue;
  text_color.a = alpha;
}

void Text::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  SDL_Rect renderQuad = { x, y, text_width, text_height };

  if( clip != NULL )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip );
}
