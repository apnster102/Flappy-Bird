#include <iostream>
#include <SDL.h>
#include "GameLoop.h"

using namespace std;

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
}

bool GameLoop::getGameState()
{
    return GameState;
}

void GameLoop::logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void GameLoop::InitSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);
    if (renderer)
    {
        cout << "Renderer created!" << endl;
        GameState = true;

        gPlayer.loadImage("image/flyGreen.png", renderer);
        gPlayer.setRect(300, 200);
        gPlayer.setSprite();

        ground.loadImage("image/ground.png", renderer);
        ground.setRect(0, SCREEN_HEIGHT-50);

        background.loadImage("image/background.png", renderer);
        background.setRect(0,0);

    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GameLoop::Event()
{
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT)
    {
        GameState = false;
    }

    gPlayer.handleEvent(event1, renderer);
}

void GameLoop::Render()
{
    gPlayer.move();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    background.render(renderer);

    ground.groundScrolling(renderer);

    //pipe.render(renderer);

    gPlayer.render(renderer);

    SDL_RenderPresent(renderer);
}

void GameLoop::QuitSDL()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
