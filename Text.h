#ifndef TEXT__H_
#define TEXT__H_

#include "Object.h"

class Text
{
public:
  Text(void);
  ~Text(void);

  bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* ren);
  void Free();

  void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

  void RenderText(SDL_Renderer* ren, int x, int y, SDL_Rect* clip = NULL,
                double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  int getWidth() const {return text_width;}
  int getHeight() const {return text_height;}
  void SetText(const string& text) {content = text;}
  string GetText() const {return content;}

private:
  string content;
  SDL_Color text_color;
  SDL_Texture* texture;
  int text_width;
  int text_height;

};








//#include "Object.h"
//
//class Text : public Object
//{
//private:
//    string content;
//    int text_width, text_height;
//    SDL_Color text_color;
//    SDL_Texture* tTexture;
//
//public:
//    Text();
//    ~Text();
//
//    bool LoadFromFile(string path);
//    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* ren);
//    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
//    void setBlendMode(SDL_BlendMode blending);
//    void render(SDL_Renderer* ren, int x, int y, SDL_Rect* clip = NULL,
//                double angle = 0.0, SDL_Point* center = NULL,
//                SDL_RendererFlip flip = SDL_FLIP_NONE );
//    void setContent(string _text);
//    void setTextSize(int _width, int _height);
//};


#endif // TEXT__H_
