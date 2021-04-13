#ifndef GAMELOOP__H_
#define GAMELOOP__H_

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "BackGround.h"
#include "Player.h"
#include "BackGround.h"
#include "Pipes.h"

class GameLoop
{
private:
	const int SCREEN_WIDTH = 960;
	const int SCREEN_HEIGHT = 540;
	const char* WINDOW_TITLE = "This is a little box";
	bool GameState;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Event event1;

	Player gPlayer;
	BackGround background, ground;
	int numOfPipes = 3;
	PipePair* pipes = new PipePair[numOfPipes];

	ofstream HighScore;

	int score;

	Mix_Music* bgMusic;
	Mix_Chunk* hit;

public:
	GameLoop();
	bool getGameState();
	void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
	void InitSDL();
	bool loadMedia();
	void Event();
	void Update();
	void Render();
	void QuitSDL();
	~GameLoop();

};



#endif
