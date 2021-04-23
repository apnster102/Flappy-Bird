#include <iostream>
#include <SDL.h>
#include "GameLoop.h"

using namespace std;

int main(int argc, char* argv[])
{
    GameLoop* game = new GameLoop();
    game->InitSDL();
    srand(time(0));

    if(game->loadMedia())
    {
        bool quitMenu = false;
        bool replay = game->getGame();

        game->PlayMusic(game->menuMusic);

        while(game->getGameState())
        {
            game->Render();

            game->Event();

        }
        game->QuitSDL();
    }

    return 0;
}
