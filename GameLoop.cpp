#include <iostream>
#include <SDL.h>
#include "GameLoop.h"

using namespace std;

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    //player = NULL;
    background = NULL;
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
        cout << "Renderer is here!";
        GameState = true;
       // player = TextureManager::Texture("image/fly1.png", renderer);

        gPlayer.loadImage("image/fly1.png", renderer);

        background = TextureManager::Texture("image/bg.png", renderer);
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

void GameLoop::Update()
{

}

void GameLoop::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, NULL);

    gPlayer.render(renderer);

    SDL_RenderPresent(renderer);
}

void GameLoop::QuitSDL()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
