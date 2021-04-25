#include "GameLoop.h"

using namespace std;

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;
    score = 0;
    highscore = GetHighScore("Score.txt");
    newhs = false;
    bgMusic = NULL;
    menuMusic = NULL;
    mouseClick = NULL;
    hit = NULL;
    punch = NULL;
    ting = NULL;
    gFont = NULL;
    menuFont = NULL;
    hsFont = NULL;
    show = "Menu";
    play = "Play";
}

bool GameLoop::getGameState()
{
    return GameState;
}

bool GameLoop::getst()
{
    return show == "Game";
}

void GameLoop::Restart()
{

    if(play == "Replay")
    {
        score = 0;
        for(int i = 0; i < numOfPipes; i++)
        {
            pipes[i].spawnPipes(renderer);
            pipes[i].setOffset(880 + i*340);
        }

        gPlayer.setLiveState(0);
        gPlayer.setRect(400, 200);

    }
    play = "Play";
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

    if(TTF_Init() != 0)
        logSDLError(cout, "Initialize Font", true);

    //HighScore.open("Score.txt");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}

bool GameLoop::loadMedia()
{
    menu.loadImage("image/Menu.jpg", renderer);
    menu.setRect(0,0);

    instruction.loadImage("image/Instruction_.jpg", renderer);
    menu.setRect(0,0);

    gPlayer.loadImage("image/flyGreen.png", renderer);
    gPlayer.setRect(400, 200);
    gPlayer.setSprite();

    ground.loadImage("image/ground.png", renderer);
    ground.setRect(0, SCREEN_HEIGHT-50);

    background.loadImage("image/background.png", renderer);
    background.setRect(0,0);

    gameoverBox.loadImage("image/Box.png", renderer);
    gameoverBox.setRect(SCREEN_WIDTH/2-gameoverBox.getRect().w/2, SCREEN_HEIGHT/2-gameoverBox.getRect().h/2);

    PlayButton.loadImage("image/button1.png", renderer);
    PlayButton.setRect(SCREEN_WIDTH/2 - PlayButton.getRect().w/2, SCREEN_HEIGHT/2 + 30);

    HelpButton.loadImage("image/button2.png", renderer);
    HelpButton.setRect(PlayButton.getPosX(), PlayButton.getRect().y + PlayButton.getRect().h + 30);

    BackButton.loadImage("image/Back.png", renderer);
    BackButton.setRect(10,10);

    ReplayButton.loadImage("image/button1.png", renderer);
    ReplayButton.setRect(SCREEN_WIDTH/2 - ReplayButton.getRect().w - 20, 335);

    ExitButton.loadImage("image/button2.png", renderer);
    ExitButton.setRect(ReplayButton.getPosX()+ReplayButton.getRect().w + 30, 335);

    for(int i = 0; i < numOfPipes; i++)
    {
        pipes[i].spawnPipes(renderer);
        pipes[i].setOffset(880 + i*340);
    }

    bgMusic = Mix_LoadMUS("sound/gumball_outro.mp3");
    if(bgMusic == NULL) GameState = false;

    menuMusic = Mix_LoadMUS("sound/gumball_-_rpg_battle.mp3");
    if(menuMusic == NULL) GameState = false;

    mouseClick = Mix_LoadWAV("sound/sound_mouse_click.wav");
    if(mouseClick == NULL) GameState = false;
    hit = Mix_LoadWAV("sound/game_over.mp3");
    Mix_VolumeChunk(hit, 50);
    if(hit == NULL) GameState = false;
    punch = Mix_LoadWAV("sound/punch.mp3");
    Mix_VolumeChunk(punch, MIX_MAX_VOLUME);
    if(punch == NULL) GameState = false;
    ting = Mix_LoadWAV("sound/flappy_bird_sms.mp3");
    if(ting == NULL) GameState = false;

    gFont = TTF_OpenFont("font/Showcard Gothic Regular.ttf", 72);
    if(gFont == NULL) GameState = false;

    menuFont = TTF_OpenFont("font/Showcard Gothic Regular.ttf", 43);
    if(menuFont == NULL) GameState = false;

    hsFont = TTF_OpenFont("font/Showcard Gothic Regular.ttf", 24);
    if(hsFont == NULL) GameState = false;

    gameover_text.SetText("GAME OVER!");
    gameover_text.loadFromRenderedText(gFont, renderer);

    newHscore_text.SetText("New High Score!");
    newHscore_text.loadFromRenderedText(hsFont, renderer);
    return GameState;
}

void GameLoop::PlayMusic(Mix_Music* music)
{
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic(music, -1);
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
            Mix_PlayMusic(music, -1);
        }
    }
}

void GameLoop::MenuEvent()
{
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
        GameState = false;
    }

    if(show == "Menu")
    {
        PlayButton.handleButtonEvent(event, mouseClick, show, "Game");
        HelpButton.handleButtonEvent(event, mouseClick, show, "Instruction");
    }
    else if(show == "Instruction")
    {
        BackButton.handleButtonEvent(event, mouseClick, show, "Menu");
    }
}

void GameLoop::GameEvent()
{
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
        GameState = false;
    }

    if(show == "Game")
    {
        gPlayer.move();
        gPlayer.handleEvent(event);

        //update score
        for (int i = 0; i < numOfPipes; i++)
        {
            if(pipes[i].passed(gPlayer.getFrameRect()) && !gPlayer.getLiveState())
            {
                Mix_PlayChannel(-1, ting, 0);
                score++;
            }
        }

        tScore = to_string(score);
        score_text.SetText(tScore);
        score_text.loadFromRenderedText(gFont, renderer);

        // game over
        for (int i = 0; i < numOfPipes; i++)
        {
            if(pipes[i].collided(gPlayer.getFrameRect()))
            {
                if(!gPlayer.getLiveState())
                {
                    Mix_PlayChannel(-1, punch, 0);

                    UpdateHighScore("Score.txt", score, highscore);
                    cout << "Score: " << score << endl;
                    Mix_PlayChannel(-1, hit, 0);
                }

                gPlayer.setLiveState(true);

            }
        }

        if(gPlayer.getLiveState())
        {
            ReplayButton.handleButtonEvent(event, mouseClick, play, "Replay");
            ExitButton.handleButtonEvent(event, mouseClick, play, "Exit");
        }

        if(play == "Exit")
        {
            GameState = false;
        }
    }
}

void GameLoop::RenderMenu()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if(show == "Menu")
    {
        menu.render(renderer);
        PlayButton.RenderButton(renderer, "PLAY", menuFont);
        HelpButton.RenderButton(renderer, "HELP", menuFont);
    }

    else if(show == "Instruction")
    {
        instruction.render(renderer);
        BackButton.RenderButton(renderer, "", menuFont);
    }

    SDL_RenderPresent(renderer);
}

void GameLoop::RenderGameWindow()
{
//    gPlayer.move();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if(show == "Game")
    {
        background.render(renderer);

        for(int i = 0; i < numOfPipes; i++)
        {
            if(!gPlayer.getLiveState())
                pipes[i].roll(renderer);
            pipes[i].render(renderer);
        }

        ground.groundScrolling(renderer);

        gPlayer.render(renderer);

        score_text.RenderText(renderer, SCREEN_WIDTH/2 , 10);
        if(gPlayer.getLiveState())
        {
            gameoverBox.render(renderer);
            gameover_text.RenderText(renderer,SCREEN_WIDTH/2-gameover_text.getWidth()/2, 150);
            highscore_text.RenderText(renderer, SCREEN_WIDTH/2-highscore_text.getWidth()/2, 250);

            ReplayButton.RenderButton(renderer, "REPLAY", menuFont);
            ExitButton.RenderButton(renderer, "EXIT", menuFont);
            if(newhs)
                newHscore_text.RenderText(renderer, SCREEN_WIDTH/2-newHscore_text.getWidth()/2, 300);
        }
    }

    SDL_RenderPresent(renderer);

}

string GameLoop::GetHighScore(string path)
{
	fstream HighScore;
	string highscore;

	HighScore.open(path, ios::in);
	HighScore >> highscore;

	return highscore;
}

void GameLoop::UpdateHighScore(string path, const int& score, const string& ohScore)
{
	int oldHighScore = 0;
	fstream HighScore;
	string newHighScore;
	stringstream ConvertToInt(ohScore);

	HighScore.open(path, ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
		highscore = to_string(score);
        newhs = true;
	}
	newHighScore = to_string(oldHighScore);

    highscore_text.SetText("HIGH SCORE: " + highscore);
    highscore_text.loadFromRenderedText(menuFont, renderer);

	HighScore << newHighScore;
}

void GameLoop::QuitSDL()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(gFont);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
