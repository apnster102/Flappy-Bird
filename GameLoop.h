#ifndef GAMELOOP__H_
#define GAMELOOP__H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "BackGround.h"
#include "Player.h"
#include "BackGround.h"
#include "Pipes.h"
#include "Text.h"
#include "Button.h"

class GameLoop
{
private:
	const int SCREEN_WIDTH = 960;
	const int SCREEN_HEIGHT = 540;
	const char* WINDOW_TITLE = "FLAPPY BIRD";

	bool GameState;
	bool restart, start;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Event event;

	Player gPlayer;
	BackGround background, ground;
	BackGround menu, instruction;
	BackGround gameoverBox;

	int numOfPipes = 3;
	PipePair* pipes = new PipePair[numOfPipes];

	int score;
	string tScore;

	string highscore;

	TTF_Font* gFont;
	TTF_Font* menuFont;
	Text score_text, highscore_text, gameover_text;


	Mix_Chunk* mouseClick;
	Mix_Chunk* hit;
	Mix_Chunk* punch;
	Mix_Chunk* ting;

	Button PlayButton, HelpButton, BackButton;
	Button ReplayButton, ExitButton;

	string show;

public:
	GameLoop();
	bool getGameState();
	bool getGame();
	void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
	void InitSDL();
	bool loadMedia();
	Mix_Music* bgMusic;
	Mix_Music* menuMusic;
	void PlayMusic(Mix_Music* music);
	void Event();
	string GetHighScore(string path);
	void UpdateHighScore(string path, const int& score, const string& ohScore);
	void Render();
	void QuitSDL();
	~GameLoop();

};



#endif
