#include <iostream>
#include <SDL.h>
#include "GameLoop.h"

GameLoop* game = new GameLoop();

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    game->InitSDL();
    if(game->loadMedia())
    {
        while(game->getGameState())
        {
            game->Render();

            game->Event();

            game->Update();
        }
        game->QuitSDL();
    }


    return 0;
}
