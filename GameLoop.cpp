#include "GameLoop.h"

using namespace std;

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    score = 0;
    bgMusic = NULL;
    hit = NULL;
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
    }

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        logSDLError(cout, "Open Audio", true);

    HighScore.open("Score.txt");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

bool GameLoop::loadMedia()
{
    gPlayer.loadImage("image/flyGreen.png", renderer);
    gPlayer.setRect(400, 200);
    gPlayer.setSprite();

    ground.loadImage("image/ground.png", renderer);
    ground.setRect(0, SCREEN_HEIGHT-50);

    background.loadImage("image/background.png", renderer);
    background.setRect(0,0);

    for(int i = 0; i < numOfPipes; i++)
    {
        pipes[i].spawnPipes(renderer);
        pipes[i].setOffset(900 + i*330);
    }

    bgMusic = Mix_LoadMUS("sound/gumball_outro.mp3");
    if(bgMusic == NULL) GameState = false;

    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( bgMusic, -1 );
    }
    else
    {
        if( Mix_PausedMusic() == 1 )
        {
            Mix_ResumeMusic();
        }
        else
        {
            Mix_PauseMusic();
        }
    }

    hit = Mix_LoadWAV("sound/ouch.mp3");

    return GameState;
}

void GameLoop::Event()
{
    SDL_PollEvent(&event1);
    if(event1.type == SDL_QUIT)
    {
        GameState = false;
    }

    gPlayer.handleEvent(event1);

    for (int i = 0; i < numOfPipes; i++)
    {
        if(pipes[i].collided(gPlayer.getFrameRect()))
        {
            if(!gPlayer.getLiveState()) Mix_PlayChannel(-1, hit, 0);
            gPlayer.setLiveState(true);
        }
    }

}

void GameLoop::Update()
{
    for (int i = 0; i < numOfPipes; i++)
    if(pipes[i].passed(gPlayer.getFrameRect())&& !gPlayer.getLiveState())
    {
        score += 10;
        HighScore << score << endl;
    }

}

void GameLoop::Render()
{
    gPlayer.move();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    background.render(renderer);

    for(int i = 0; i < numOfPipes; i++)
    {
        if(!gPlayer.getLiveState())
            pipes[i].roll(renderer);
        pipes[i].render(renderer);
    }

    ground.groundScrolling(renderer);

    gPlayer.render(renderer);

    SDL_RenderPresent(renderer);
}

void GameLoop::QuitSDL()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
