#include <iostream>
#include <SDL.h>
#include "GameLoop.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));

    GameLoop* game = new GameLoop();

    game->InitSDL();

    if(game->loadMedia())
    {
        bool quitMenu = false;
        bool playing = false;
        game->PlayMusic(game->menuMusic);

        while(!quitMenu && game->getGameState())
        {
            game->RenderMenu();
            game->MenuEvent();
            quitMenu = game->getst();
        }
        playing = true;
        game->PlayMusic(game->bgMusic);

        do
        {
            game->Restart();
            game->RenderGameWindow();
            game->GameEvent();
        }while(playing && game->getGameState());

        game->QuitSDL();
    }


    return 0;
}
