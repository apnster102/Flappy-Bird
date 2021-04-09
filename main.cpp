#include <iostream>
#include <SDL.h>
#include "GameLoop.h"

GameLoop* game = new GameLoop();

using namespace std;

int main(int argc, char* argv[])
{
    game->InitSDL();
    srand(time(0));
    while(game->getGameState())
    {
        game->Render();

        game->Update();

        game->Event();
    }
    game->QuitSDL();
    return 0;
}
